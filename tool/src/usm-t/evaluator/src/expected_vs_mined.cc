#include "EdgeProposition.hh"
#include "Location.hh"
#include "Test.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include <algorithm>
#include <filesystem>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

//spot includes
#include "AutomataBasedEvaluator.hh"
#include "spot/twa/bddprint.hh"
#include "spot/twa/twa.hh"
#include "spot/twa/twagraph.hh"
#include "spot/twaalgos/translate.hh"
#include <spot/tl/formula.hh>
#include <spot/tl/ltlf.hh>
#include <spot/tl/parse.hh>
#include <spot/tl/print.hh>
#include <spot/twaalgos/contains.hh>
#include <spot/twaalgos/hoa.hh>
#include <spot/twaalgos/isdet.hh>
#include <spot/twaalgos/postproc.hh>
#include <spot/twaalgos/remprop.hh>
#include <z3++.h>

#include "Assertion.hh"
#include "CSVtraceReader.hh"
#include "EvalReport.hh"
#include "ProgressBar.hpp"
#include "Trace.hh"
#include "VCDtraceReader.hh"
#include "assertion_utils.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "usmt-evaluator.hh"

#include "gedlibWrapper.hh"
#include "z3CheckSat.hh"

//normal include
namespace usmt {
using namespace harm;

void evaluateWithEditDistance(
    ExpectedVSMinedReportPtr &report,
    const std::vector<AssertionPtr> &expectedAssertions,
    const std::vector<AssertionPtr> &minedAssertions, TracePtr trace);

int compareLanguage(harm::AssertionPtr a1, harm::AssertionPtr a2) {
  //ret 0 if equivalent, 1 if a1 contains/implies/covers a2, 2 if a2 contains/implies/covers a1, -1 if not

  std::string a1_str = a1->toString(Language::SpotLTL);
  std::string a2_str = a2->toString(Language::SpotLTL);

  spot::formula p1 = spot::parse_formula(a1_str);
  spot::formula p2 = spot::parse_formula(a2_str);

  if (spot::are_equivalent(p1, p2)) {
    return 0;
  } else {
    if (spot::contains(p1, p2) == 1) {
      return 1;
    } else if (spot::contains(p2, p1) == 1) {
      return 2;
    }
  }
  return -1;
}

EvalReportPtr
evaluateExpectedvsMined(const usmt::UseCase &use_case,
                        const std::string expected_assertion_path) {

  const UseCasePathHandler &ph = use_case.ph;

  TracePtr trace = parseInputTraces(use_case);
  auto expected_assertions =
      getAssertionsFromFile(expected_assertion_path, trace);
  messageErrorIf(expected_assertions.empty(),
                 "No expected assertions found in " +
                     expected_assertion_path);

  ExpectedVSMinedReportPtr ret =
      std::make_shared<ExpectedVSMinedReport>();

  ret->_totExpected = expected_assertions.size();

  for (const auto &output : use_case.output) {
    std::string adapted_output_folder =
        ph.work_path + "adapted/" + output.path;
    auto mined_assertions =
        getAssertionsFromFile(adapted_output_folder, trace);

    evaluateWithEditDistance(ret, expected_assertions,
                             mined_assertions, trace);

    //progresscpp::ParallelProgressBar pb;

    //for (const auto &ea : expected_assertions) {
    //  std::string expected_assertion_str = ea->toString();
    //  pb.addInstance(0, "Comparing " + expected_assertion_str,
    //                 mined_assertions.size(), 70);
    //  for (const auto &ma : mined_assertions) {
    //    int res = compareLanguage(ea, ma);

    //    if (res == 0) {
    //      ret->_expectedCoveredWith.emplace_back(ea->toString(),
    //                                             ma->toString());
    //      pb.changeMessage(0, "Comparing " + expected_assertion_str +
    //                              " Covered!");
    //      pb.display();
    //      break;
    //    } else if (res != -1) {
    //      ret->_expextedToSimilar[ea->toString()].push_back(
    //          ma->toString());
    //    }
    //    size_t nOfSimilarAssertions =
    //        ret->_expextedToSimilar.count(expected_assertion_str)
    //            ? ret->_expextedToSimilar.at(expected_assertion_str)
    //                  .size()
    //            : 0;

    //    pb.changeMessage(0, "Comparing " + expected_assertion_str +
    //                            " " +
    //                            std::to_string(nOfSimilarAssertions));
    //    pb.increment(0);
    //    pb.display();
    //  }

    //  pb.done(0);
    //}
  }

  //remove redudant _expectedCoveredWith
  std::sort(ret->_expectedCoveredWith.begin(),
            ret->_expectedCoveredWith.end(),
            [](const auto &a, const auto &b) { return a < b; });
  ret->_expectedCoveredWith.erase(
      std::unique(ret->_expectedCoveredWith.begin(),
                  ret->_expectedCoveredWith.end()),
      ret->_expectedCoveredWith.end());

  ret->_score = (double)ret->_expectedCoveredWith.size() /
                (double)ret->_totExpected;
  return ret;
}

void evaluateWithEditDistance(
    ExpectedVSMinedReportPtr &report,
    const std::vector<AssertionPtr> &expectedAssertions,
    const std::vector<AssertionPtr> &minedAssertions,
    TracePtr trace) {

  std::unordered_map<AssertionPtr, SerializedAutomaton>
      expectedToSAutomaton;

  std::unordered_map<AssertionPtr, SerializedAutomaton>
      minedToSAutomaton;

  for (const auto &ea : expectedAssertions) {
    //Extract the automaton without the G
    AutomataBasedEvaluatorPtr ea_eval =
        generatePtr<AutomataBasedEvaluator>(
            ea->_formula->getItems()[0], trace);
    Automaton *aut = ea_eval->getAutomaton();
    expectedToSAutomaton[ea] = serializeAutomaton(aut);
  }

  for (const auto &ma : minedAssertions) {
    //Extract the automaton without the G
    AutomataBasedEvaluatorPtr ma_eval =
        generatePtr<AutomataBasedEvaluator>(
            ma->_formula->getItems()[0], trace);
    Automaton *aut = ma_eval->getAutomaton();
    minedToSAutomaton[ma] = serializeAutomaton(aut);
  }

  static std::map<std::pair<std::string, std::string>, double>
      edge_rel_cost_map;

  std::unordered_set<std::string> all_edge_labels;
  std::unordered_map<std::string, PropositionPtr>
      all_edgeToProposition;

  for (const auto &[ea, ea_sa] : expectedToSAutomaton) {
    for (auto &[from, to, label] : ea_sa.edges) {
      all_edge_labels.insert(label);
      all_edgeToProposition[label] =
          hparser::parseProposition(label, trace);
    }
  }

  for (const auto &[ma, ma_sa] : minedToSAutomaton) {
    for (auto &[from, to, label] : ma_sa.edges) {
      all_edge_labels.insert(label);
      all_edgeToProposition[label] =
          hparser::parseProposition(label, trace);
    }
  }

  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Computing edge relabling cost",
                 all_edge_labels.size() * all_edge_labels.size(), 70);
  //the cost to all couples of edges
  for (const auto &label1 : all_edge_labels) {
    for (const auto &label2 : all_edge_labels) {
      if (edge_rel_cost_map.count(std::make_pair(label1, label2))) {
        pb.increment(0);
        pb.display();
        continue;
      }
      if (label1 == label2) { //optimization
        edge_rel_cost_map[std::make_pair(label1, label2)] = 0.0;
      } else if ((label1 == "true" && label2 != "true") ||
                 (label2 == "true" && label1 != "true")) {
        edge_rel_cost_map[std::make_pair(label1, label2)] = 1.0;
      } else if (z3::check_implies(
                     all_edgeToProposition.at(label1),
                     all_edgeToProposition.at(label2))) {
        //std::cout << label1 << " -> " << label2 << "\n";
        edge_rel_cost_map[std::make_pair(label1, label2)] = 0.5;
      } else {
        //std::cout << label1 << " -/> " << label2 << "\n";
        edge_rel_cost_map[std::make_pair(label1, label2)] = 1.0;
      }

      pb.increment(0);
      pb.display();
    }
  }
  pb.done(0);

  //fix cost for syntatically different but semantically equivalent edges
  for (const auto &label1 : all_edge_labels) {
    for (const auto &label2 : all_edge_labels) {
      if (edge_rel_cost_map.at(std::make_pair(label1, label2)) ==
              0.5 &&
          edge_rel_cost_map.at(std::make_pair(label2, label1)) ==
              0.5) {
        edge_rel_cost_map[std::make_pair(label1, label2)] = 0.0;
        edge_rel_cost_map[std::make_pair(label2, label1)] = 0.0;
      }
    }
  }

  for (const auto &[ea, ea_sa] : expectedToSAutomaton) {
    for (const auto &[ma, ma_sa] : minedToSAutomaton) {
      computeEditDistance(ea, ea_sa, ma, ma_sa, edge_rel_cost_map);
    }
  }
}

} // namespace usmt
