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
TracePtr generateMockTrace(size_t number_of_variables) {

  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < number_of_variables; i++) {
    //vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
    //vars.emplace_back("f_" + std::to_string(i), ExpType::Float, 64);
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
  return ret;
}

TEST(semantically_equivalence_scalabilityTests,
     semantically_equivalence_next) {

  std::vector<AssertionPtr> expected_assertions =
      makeAssertionsFromTemplate("..##1..", 3, 3, 1000, 100);

  std::vector<AssertionPtr> mined_assertions = expected_assertions;

  SemanticEquivalenceReportPtr report =
      std::make_shared<SemanticEquivalenceReport>();

  auto flattenedAssertions =
      getFlattenedAssertions(expected_assertions, mined_assertions);

  std::cout << "Number of comparisons: "
            << expected_assertions.size() * mined_assertions.size()
            << "\n";

  evaluateWithSemanticComparison(report, flattenedAssertions);
}

//TEST(semantically_equivalence_scalabilityTests, semantically_equivalence_and) {
//
//  std::vector<AssertionPtr> assertions =
//      makeAssertionsFromTemplate("..&&..", 3, 3, 1000, 100);
//  std::unordered_map<std::string, std::vector<FlattenedAssertion>>
//      assertions_map;
//
//  for (auto &a : assertions) {
//    assertions_map["expected"].emplace_back(a, a->toString());
//  }
//  for (auto &a : assertions) {
//    assertions_map["mined"].emplace_back(a, a->toString());
//  }
//
//  SemanticEquivalenceReportPtr report =
//      std::make_shared<SemanticEquivalenceReport>();
//
//  std::cout << "Number of comparisons: "
//            << assertions_map["expected"].size() *
//                   (assertions_map["mined"].size())
//            << "\n";
//  evaluateWithSemanticComparison(report, assertions_map);
//}

