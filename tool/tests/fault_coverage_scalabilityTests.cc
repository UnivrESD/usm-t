#include <filesystem>
#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

#include "Assertion.hh"
#include "AutomataBasedEvaluator.hh"
#include "CSVtraceReader.hh"
#include "EvalReport.hh"
#include "Evaluator.hh"
#include "FlattenedAssertion.hh"
#include "ProgressBar.hpp"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "TraceReader.hh"
#include "assertion_utils.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "usmt-evaluator.hh"
#include "visitors/ExpToZ3Visitor.hh"
#include "z3TestCaseGenerator.hh"
#include "gtest/gtest_pred_impl.h"
#include <chrono>

using namespace harm;
using namespace usmt;
using TraceReaderPtr = std::shared_ptr<TraceReader>;

TracePtr generateMockTrueTrace(size_t number_of_variables,
                               size_t length) {

  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < number_of_variables; i++) {
    vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
  }

  TracePtr trace = generatePtr<Trace>(vars, length);
  for (auto &v : vars) {
    BooleanVariablePtr bv = trace->getBooleanVariable(v.getName());
    for (size_t i = 0; i < length; ++i) {
      bv->assign(i, true);
    }
  }
  return trace;
}

TracePtr generateMockRandomTrace(size_t number_of_variables,
                                 size_t length) {

  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < number_of_variables; i++) {
    vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
  }

  TracePtr trace = generatePtr<Trace>(vars, length);
  size_t which_var_to_fault = rand() % vars.size();
  for (int j = 0; j < vars.size(); ++j) {
    auto &v = vars[j];
    BooleanVariablePtr bv = trace->getBooleanVariable(v.getName());
    for (size_t i = 0; i < length; ++i) {
      bv->assign(i, j == which_var_to_fault ? false : true);
    }
  }
  return trace;
}

std::pair<std::vector<AssertionPtr>, TracePtr>
makeAssertionsFromTemplate(std::string _template,
                           size_t max_ant_length,
                           size_t max_con_length,
                           size_t number_to_make,
                           size_t max_number_of_variables,
                           size_t trace_length) {
  std::vector<AssertionPtr> ret;
  TracePtr trace =
      generateMockTrueTrace(max_number_of_variables, trace_length);
  auto all_vars = trace->getVariables();
  const std::string assertion_prefix = "G(";
  const std::string assertion_postfix = ")";

  if (_template == "..&&..") {
    for (size_t i = 0; i < number_to_make; i++) {
      //make antecedent
      std::string assertionStr_tmp = assertion_prefix;
      size_t ant_length = rand() % max_ant_length + 1;
      for (size_t j = 0; j < ant_length; j++) {
        std::string randomVarName =
            all_vars[rand() % all_vars.size()].getName();
        assertionStr_tmp += randomVarName;
        if (j != ant_length - 1) {
          assertionStr_tmp += " && ";
        }
      }
      assertionStr_tmp += " -> ";
      //make consequent
      size_t on_length = rand() % max_con_length + 1;
      for (size_t j = 0; j < on_length; j++) {
        std::string randomVarName =
            all_vars[rand() % all_vars.size()].getName();
        assertionStr_tmp += randomVarName;
        if (j != on_length - 1) {
          assertionStr_tmp += " && ";
        }
      }

      assertionStr_tmp += assertion_postfix;

      //debug
      //std::cout << "Assertion: " << assertionStr_tmp << "\n";
      ret.push_back(makeAssertion(assertionStr_tmp, trace));
    }
  } else if (_template == "..##1..") {
    for (size_t i = 0; i < number_to_make; i++) {
      //make antecedent
      std::string assertionStr_tmp = assertion_prefix + "{";
      size_t ant_length = rand() % max_ant_length + 1;
      for (size_t j = 0; j < ant_length; j++) {
        std::string randomVarName =
            all_vars[rand() % all_vars.size()].getName();
        assertionStr_tmp += randomVarName;
        if (j != ant_length - 1) {
          assertionStr_tmp += " ##1 ";
        }
      }
      assertionStr_tmp += "} |-> ";
      //make consequent
      size_t on_length = rand() % max_con_length + 1;
      for (size_t j = 0; j < on_length; j++) {
        std::string randomVarName =
            all_vars[rand() % all_vars.size()].getName();
        assertionStr_tmp += randomVarName;
        if (j != on_length - 1) {
          assertionStr_tmp += " ##1 ";
        }
      }

      assertionStr_tmp += assertion_postfix;

      //debug
      //std::cout << "Assertion: " << assertionStr_tmp << "\n";
      ret.push_back(makeAssertion(assertionStr_tmp, trace));
    }
  }
  return {ret, trace};
}

TEST(fault_coverage_scalabilityTests, fault_coverage_next) {

  std::vector<AssertionPtr> assertions;
  size_t number_of_faults = 1000;
  size_t trace_length = 10000;
  size_t max_number_of_variables = 100;
  size_t number_of_assertions_to_make = 1000;

  auto assertions_trace = makeAssertionsFromTemplate(
      "..##1..", 3, 3, number_of_assertions_to_make,
      max_number_of_variables, trace_length);
  assertions = assertions_trace.first;
  TracePtr golden_trace = assertions_trace.second;
  //make a directory "faulty_traces" in '/tmp' and put the faulty traces there
  std::string faulty_traces = "/tmp/faulty_traces";
  //delete the directory if it exists
  if (std::filesystem::exists(faulty_traces)) {
    std::filesystem::remove_all(faulty_traces);
  }
  std::filesystem::create_directory(faulty_traces);
  fault_coverage_t fc_result;
  for (size_t i = 0; i < number_of_faults; i++) {
    TracePtr trace = generateMockRandomTrace(max_number_of_variables,
                                             trace_length);
    std::string trace_path =
        faulty_traces + "/faulty_" + std::to_string(i) + ".csv";
    dumpTraceAsCSV(trace, trace_path);
    fc_result._faultyTraceFiles.push_back(trace_path);
  }

  clc::parserType = "csv";
  FaultCoverageReportPtr report =
      std::make_shared<FaultCoverageReport>();
  evaluateWithFaultCoverage(assertions, golden_trace, fc_result);
}

