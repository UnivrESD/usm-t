#include <gtest/gtest-message.h>
#include <gtest/gtest-test-part.h>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

#include "Assertion.hh"
#include "AutomataBasedEvaluator.hh"
#include "EdgeProposition.hh"
#include "Evaluator.hh"
#include "ProgressBar.hpp"
#include "TemplateImplication.hh"
#include "Trace.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include "propositionParsingUtils.hh"
#include "simulation_based.hh"
#include "spot/twa/bddprint.hh"
#include "spot/twa/twa.hh"
#include "spot/twa/twagraph.hh"
#include "spot/twaalgos/translate.hh"
#include "temporalParsingUtils.hh"
#include "usmt-evaluator.hh"
#include "visitors/ExpToZ3Visitor.hh"
#include "z3TestCaseGenerator.hh"
#include "gtest/gtest_pred_impl.h"
#include <chrono>
#include <spot/tl/formula.hh>
#include <spot/tl/parse.hh>
#include <spot/tl/print.hh>
#include <spot/twaalgos/isdet.hh>
#include <spot/twaalgos/postproc.hh>

using namespace harm;
using namespace usmt;

TEST(gatherPathTest, gp1) {

  std::vector<VarDeclaration> vars;
  for (size_t i = 0; i < 100; i++) {
    vars.emplace_back("b_" + std::to_string(i), ExpType::Bool, 1);
    vars.emplace_back("f_" + std::to_string(i), ExpType::Float, 64);
    vars.emplace_back("i_" + std::to_string(i), ExpType::SInt, 64);
  }

  const TracePtr &trace = generatePtr<Trace>(vars, 1);

  std::string originalFormula = "G({b_0 ##1 b_1}|->b_2)";

  TemporalExpressionPtr harm_formula =
      hparser::parseTemporalExpression(originalFormula, trace);

  std::string spotFormulaStr =
      temp2String(harm_formula, Language::SpotLTL, PrintMode::Hide);

  //retrieve the spot formula
  spot::formula spotFormula = spot::parse_infix_psl(spotFormulaStr).f;
  //generate the spot automaton
  std::shared_ptr<spot::twa_graph> spotAutomaton =
      generateDeterministicSpotAutomaton(spotFormula);
  auto placeholderPack = extractPlaceholders(harm_formula);

  //build the harm automaton
  auto automaton =
      buildAutomatonFromSpot(spotAutomaton, placeholderPack);

  std::vector<std::vector<harm::Automaton::Edge *>> paths =
      getPaths(automaton->_root, 10,2);
  messageInfo("Found " + std::to_string(paths.size()) + " paths");

  //print the paths
  for (auto &path : paths) {
    for (auto &edge : path) {
      std::cout << edge->_prop->toString() << " -> ";
    }
    std::cout << "\n";
  }
}

