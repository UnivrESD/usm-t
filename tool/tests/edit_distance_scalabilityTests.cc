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
#include <z3++.h>

using namespace harm;
using namespace usmt;
using TraceReaderPtr = std::shared_ptr<TraceReader>;
TracePtr generateMockTrace(size_t number_of_variables) {

  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < number_of_variables; i++) {
    //vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
    vars.emplace_back("i_" + std::to_string(i), ExpType::UInt, 32);
  }

  return generatePtr<Trace>(vars, 1);
}
std::vector<AssertionPtr> makeAssertionsFromTemplate(
    std::string _template, size_t max_ant_length,
    size_t max_con_length, size_t number_to_make,
    size_t max_number_of_variables) {
  std::vector<AssertionPtr> ret;
  TracePtr trace = generateMockTrace(max_number_of_variables);
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
        assertionStr_tmp +=
            "(" + randomVarName + +" + " + randomVarName + ") > 0";
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
        assertionStr_tmp +=
            "(" + randomVarName + +" + " + randomVarName + ") > 0";
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
  return ret;
}

//TEST(edit_distance_scalabilityTests, edit_distance_next) {
//  //handleErrors();
//
//  std::vector<AssertionPtr> assertions =
//      makeAssertionsFromTemplate("..##1..", 3, 3, 100, 100);
//  std::unordered_map<std::string, std::vector<AssertionPtr>>
//      assertions_map;
//  assertions_map["expected"] = assertions;
//  assertions_map["mined"] = assertions;
//
//  EditDistanceReportPtr report =
//      std::make_shared<EditDistanceReport>();
//
//  std::cout << "Number of comparisons: "
//            << assertions_map["expected"].size() *
//                   (assertions_map["mined"].size())
//            << "\n";
//  evaluateWithEditDistance(report, assertions_map);
//}

extern size_t time_spent_by_z3;
TEST(edit_distance_scalabilityTests, edit_distance_and) {
  //TracePtr trace = generateMockTrace(10);
  //BooleanVariablePtr b_0 = trace->getBooleanVariable("b_0");
  //BooleanVariablePtr b_1 = trace->getBooleanVariable("b_1");
  //PropositionPtr imp =
  //    makeGenericExpression<PropositionImplication>(b_0, b_1);
  //std::cout << prop2ColoredString(imp) << "\n";
  //auto z3_expr = expression::to_z3exp(imp);
  //std::cout << *z3_expr._exp << "\n";
  //clc::psilent = 1;

  std::vector<AssertionPtr> assertions =
      makeAssertionsFromTemplate("..##1..", 3, 3, 1000, 100);
  std::unordered_map<std::string, std::vector<AssertionPtr>>
      assertions_map;
  assertions_map["expected"] = assertions;
  assertions_map["mined"] = assertions;

  EditDistanceReportPtr report =
      std::make_shared<EditDistanceReport>();

  std::cout << "Number of comparisons: "
            << assertions_map["expected"].size() *
                   (assertions_map["mined"].size())
            << "\n";
  evaluateWithEditDistance(report, assertions_map);
  std::cout << "z3 time:" << time_spent_by_z3 / 1000.f << "s\n";
}

