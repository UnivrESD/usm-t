#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

#include "Assertion.hh"
#include "AutomataBasedEvaluator.hh"
#include "Evaluator.hh"
#include "ProgressBar.hpp"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include "temporalParsingUtils.hh"
#include "usmt-evaluator.hh"
#include "gtest/gtest_pred_impl.h"
#include <chrono>

using namespace harm;
using namespace usmt;

AssertionPtr makeAssertion(const std::string &ass_str,
                           const TracePtr &trace) {
  TemplateImplicationPtr ti = hparser::parseTemplateImplication(
      ass_str, trace, harm::DTLimits(), 0);
  AssertionPtr new_ass = generatePtr<Assertion>();
  fillAssertion(new_ass, ti, false);
  return new_ass;
}

TEST(LanguageCompare, lc1) {

  std::string input_file = "../tests/input/formula_and.txt";
  std::fstream ass(input_file);

  std::string line = "";
  std::vector<std::string> assStrs;
  while (std::getline(ass, line)) {
    assStrs.push_back(line);
  }
  messageErrorIf(assStrs.empty(), "No assertions as input");

  std::vector<TemplateImplicationPtr> ret;
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Parsing assertions...", assStrs.size(), 70);

  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < 100; i++) {
    vars.emplace_back("a_" + std::to_string(i), ExpType::Bool, 1);
    vars.emplace_back("c_" + std::to_string(i), ExpType::Bool, 1);
  }

  std::vector<AssertionPtr> assertions;
  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  for (size_t i = 0; i < assStrs.size(); i++) {
    assertions.push_back(makeAssertion(assStrs[i], trace));

    pb.increment(0);
    pb.display();
  }
  pb.done(0);
  std::cout << "N assertions:" << assertions.size() << "\n";

  //std::string target_formula = "G(a_1 -> c_1)";
  //AssertionPtr targetAssertion = makeAssertion(target_formula, trace);

  //  for (auto &ass : assertions) {
  //    for (size_t i = 0; i < 100; i++) {
  //      int res = compareLanguage(ass, targetAssertion);
  //      std::cout << ass->toString(Language::SpotLTL) << " vs ";
  //      std::cout << target_formula << ": ";
  //      std::cout << res << " = ";
  //      res = testImplication(ass, targetAssertion);
  //      std::cout << res << "\n";
  //    }
  //  }

  size_t times = 1;
  //use chrono to measure time
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  for (size_t k = 0; k < assertions.size(); k++) {
    AssertionPtr targetAssertion = assertions[k];
    for (auto &ass : assertions) {
      for (size_t i = 0; i < times; i++) {
        int res = compareLanguage(ass, targetAssertion);
        //std::cout << ass->toString(Language::SpotLTL) << " vs ";
        //std::cout << targetAssertion->toString() << ": ";
        //std::cout << res;
        //std::cout <<  "\n";
      }
    }
  }
  std::chrono::steady_clock::time_point end =
      std::chrono::steady_clock::now();

  std::cout << "Time with compare "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   end - begin)
                   .count()
            << "[ms]" << std::endl;

  begin = std::chrono::steady_clock::now();
  for (size_t k = 0; k < assertions.size(); k++) {
    AssertionPtr targetAssertion = assertions[k];
    for (auto &ass : assertions) {
      for (size_t i = 0; i < times; i++) {
        int res = testEmpty(ass, targetAssertion);
      }
    }
  }
  end = std::chrono::steady_clock::now();

  std::cout << "Time with empty "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   end - begin)
                   .count()
            << "[ms]" << std::endl;
}
