#include "EdgeProposition.hh"
#include "Location.hh"
#include "Test.hh"
#include "exp.hh"
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

static std::map<std::pair<std::string, std::string>, double>
    edge_rel_cost_map;

void evaluateWithEditDistance(
    ExpectedVSMinedReportPtr &report,
    const std::unordered_map<std::string,
                             std::vector<FlattenedAssertion>>
        &flattenedAssertions);

struct FlattenedAssertion {
  AssertionPtr original;
  std::string flattened_str;
};

int compareLanguage(const FlattenedAssertion &a1,
                    const FlattenedAssertion &a2) {
  //ret 0 if equivalent, 1 if a1 contains/implies/covers a2, 2 if a2 contains/implies/covers a1, -1 if not
  spot::formula p1 = spot::parse_formula(a1.flattened_str);
  spot::formula p2 = spot::parse_formula(a2.flattened_str);

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

std::vector<BooleanLayerInstPtr>
getBooleaLayerInst(const AssertionPtr &a) {
  const TemporalExpressionPtr &te = a->_formula;
  std::vector<BooleanLayerInstPtr> ret;
  traverse(te, [&](const TemporalExpressionPtr &current) {
    if (isInst(current)) {
      ret.push_back(
          std::dynamic_pointer_cast<BooleanLayerInst>(current));
    }
    return false;
  });
  return ret;
}

std::unordered_map<std::string, std::vector<FlattenedAssertion>>
getFlattenedAssertions(const usmt::UseCase &use_case,
                       const std::string expected_assertion_path) {
  std::unordered_map<std::string, std::vector<FlattenedAssertion>>
      ret;

  const UseCasePathHandler &ph = use_case.ph;
  TracePtr trace = parseInputTraces(use_case);
  auto expected_assertions =
      getAssertionsFromFile(expected_assertion_path, trace);
  messageErrorIf(expected_assertions.empty(),
                 "No expected assertions found in " +
                     expected_assertion_path);

  std::unordered_map<std::string, PropositionPtr>
      all_rtarget_toProposition;

  //gather all remap targets--------------------------
  for (const auto &a : expected_assertions) {
    auto insts = getBooleaLayerInst(a);
    for (const auto &i : insts) {
      PropositionPtr p = i->getProposition();
      std::unordered_map<std::string, PropositionPtr> rtargets =
          prop2RemapTargets(p);
      all_rtarget_toProposition.insert(rtargets.begin(),
                                       rtargets.end());
    }
  }

  std::vector<AssertionPtr> mined_assertions;
  for (const auto &output : use_case.output) {
    std::string adapted_output_folder =
        ph.work_path + "adapted/" + output.path;
    auto mined_assertions_tmp =
        getAssertionsFromFile(adapted_output_folder, trace);
    mined_assertions.insert(mined_assertions.end(),
                            mined_assertions_tmp.begin(),
                            mined_assertions_tmp.end());

    for (const auto &a : mined_assertions) {
      auto insts = getBooleaLayerInst(a);
      for (const auto &i : insts) {
        PropositionPtr p = i->getProposition();
        std::unordered_map<std::string, PropositionPtr> rtargets =
            prop2RemapTargets(p);
        all_rtarget_toProposition.insert(rtargets.begin(),
                                         rtargets.end());
      }
    }
  }

  //semanticaly reduce the remap targets

  //---------------------------------------------------

  std::unordered_map<std::string, std::string> targetToRemap;
  //perform remapping
  size_t tokenID = 0;
  for (const auto &[rt1, p1] : all_rtarget_toProposition) {
    for (const auto &[rt2, p2] : all_rtarget_toProposition) {
      if (p1 == nullptr || p2 == nullptr) {
        continue;
      }
    }
  }
  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Mergin semanticaly equivalent propositions",
                 all_rtarget_toProposition.size(), 70);
  std::unordered_map<std::string, std::set<std::string>>
      semantically_equivalent;
  for (auto it1 = all_rtarget_toProposition.begin();
       it1 != all_rtarget_toProposition.end(); it1++) {
    auto &[rt1, p1] = *it1;
    if (p1 == nullptr) {
      pb.increment(0);
      pb.display();
      continue;
    } else {
      semantically_equivalent[rt1];
    }
    for (auto it2 = std::next(it1);
         it2 != all_rtarget_toProposition.end(); it2++) {
      auto &[rt2, p2] = *it2;
      if (p2 == nullptr || it1 == it2) {
        continue;
      }

      bool p1_implies_p2 = false;
      bool p2_implies_p1 = false;
      if (edge_rel_cost_map.count(std::make_pair(rt1, rt2))) {
        p1_implies_p2 =
            edge_rel_cost_map.at(std::make_pair(rt1, rt2)) != 0.0;
      } else {
        p1_implies_p2 = z3::check_implies(p1, p2);
        edge_rel_cost_map[std::make_pair(rt1, rt2)] =
            p1_implies_p2 ? 0.5 : 0;
      }
      if (edge_rel_cost_map.count(std::make_pair(rt2, rt1))) {
        p2_implies_p1 =
            edge_rel_cost_map.at(std::make_pair(rt2, rt1)) != 0.0;
      } else {
        p2_implies_p1 = z3::check_implies(p2, p1);
        edge_rel_cost_map[std::make_pair(rt2, rt1)] =
            p2_implies_p1 ? 0.5 : 0;
      }

      if (p1_implies_p2 && p2_implies_p1) {
        edge_rel_cost_map[std::make_pair(rt2, rt1)] = 1.0;
        edge_rel_cost_map[std::make_pair(rt1, rt2)] = 1.0;
        semantically_equivalent[rt1].insert(rt2);
        p2 = nullptr;
      }

    } //end for it2
    pb.increment(0);
    pb.display();
  }
  pb.done(0);
  //print semantically equivalent'
  //for (const auto &[rt, eqs] : semantically_equivalent) {
  //  std::cout << rt << " is semantically equivalent to: ";
  //  for (const auto &eq : eqs) {
  //    std::cout << eq << " ";
  //  }
  //  std::cout << "\n";
  //}
  //exit(0);

  for (const auto &[representant, equivalents] :
       semantically_equivalent) {
    targetToRemap[representant] =
        "__rt" + std::to_string(tokenID) + "__";
    for (auto eq : equivalents) {
      targetToRemap[eq] = "__rt" + std::to_string(tokenID) + "__";
    }
    tokenID++;
  }

  //retrive flattened expected assertions
  for (const auto &a : expected_assertions) {
    auto flattened_str =
        temp2RemapString(a->_formula->getItems()[0], targetToRemap,
                         Language::SpotLTL, PrintMode::ShowAll);
    ret["expected"].push_back({a, flattened_str});
  }

  //retrieve flattened mined assertions
  for (const auto &a : mined_assertions) {
    auto flattened_str =
        temp2RemapString(a->_formula->getItems()[0], targetToRemap,
                         Language::SpotLTL, PrintMode::ShowAll);
    ret["mined"].push_back({a, flattened_str});
  }
  return ret;
}

void compareLanguageExpectedVsMined(
    ExpectedVSMinedReportPtr report,
    const std::unordered_map<std::string,
                             std::vector<FlattenedAssertion>>
        &flattenedAssertions) {

  progresscpp::ParallelProgressBar pb;

  const std::vector<FlattenedAssertion> &expected_assertions =
      flattenedAssertions.at("expected");
  report->_totExpected = expected_assertions.size();

  const std::vector<FlattenedAssertion> &mined_assertions =
      flattenedAssertions.at("mined");

  pb.addInstance(0, "Semantic Matching...",
                 expected_assertions.size(), 70);

  for (const auto &fea : expected_assertions) {
    for (const auto &fma : mined_assertions) {
      int res = compareLanguage(fea, fma);

      if (res == 0) {
        report->_expectedCoveredWith.emplace_back(
            fea.original->toString(), fma.original->toString());
        pb.display();
        break;
      } else if (res != -1) {
        report->_expextedToSimilar[fea.original->toString()]
            .push_back(fma.original->toString());
      }

      std::string expected_assertion_str = fea.original->toString();
      size_t nOfSimilarAssertions =
          report->_expextedToSimilar.count(expected_assertion_str)
              ? report->_expextedToSimilar.at(expected_assertion_str)
                    .size()
              : 0;
    }

    pb.increment(0);
    pb.display();
  }
  pb.done(0);

  //remove redudant _expectedCoveredWith
  std::sort(report->_expectedCoveredWith.begin(),
            report->_expectedCoveredWith.end(),
            [](const auto &a, const auto &b) { return a < b; });
  report->_expectedCoveredWith.erase(
      std::unique(report->_expectedCoveredWith.begin(),
                  report->_expectedCoveredWith.end()),
      report->_expectedCoveredWith.end());

  report->_score = (double)report->_expectedCoveredWith.size() /
                   (double)report->_totExpected;
}

EvalReportPtr
evaluateExpectedvsMined(const usmt::UseCase &use_case,
                        const std::string expected_assertion_path) {

  ExpectedVSMinedReportPtr ret =
      std::make_shared<ExpectedVSMinedReport>();

  auto flattenedAssertions =
      getFlattenedAssertions(use_case, expected_assertion_path);

  for (const auto &output : use_case.output) {
    compareLanguageExpectedVsMined(ret, flattenedAssertions);

    evaluateWithEditDistance(ret, flattenedAssertions);
  }

  return ret;
}

void evaluateWithEditDistance(
    ExpectedVSMinedReportPtr &report,
    const std::unordered_map<std::string,
                             std::vector<FlattenedAssertion>>
        &flattenedAssertions) {

  std::unordered_map<AssertionPtr, SerializedAutomaton>
      expectedToSAutomaton;

  std::unordered_map<AssertionPtr, SerializedAutomaton>
      minedToSAutomaton;

  const std::vector<FlattenedAssertion> &expectedAssertions =
      flattenedAssertions.at("expected");
  const std::vector<FlattenedAssertion> &minedAssertions =
      flattenedAssertions.at("mined");

  for (const auto &[ea, flattened_str] : expectedAssertions) {
    //Extract the automaton without the G
    Automaton *aut =
        generateAutomatonFromTemporal(ea->_formula->getItems()[0]);
    expectedToSAutomaton[ea] = serializeAutomaton(aut);
  }

  for (const auto &[ma, flattened_str] : minedAssertions) {
    //Extract the automaton without the G
    Automaton *aut =
        generateAutomatonFromTemporal(ma->_formula->getItems()[0]);
    minedToSAutomaton[ma] = serializeAutomaton(aut);
  }

  progresscpp::ParallelProgressBar pb;
  pb.addInstance(
      0, "Computing Edit Distance Similarity...",
      expectedToSAutomaton.size() * minedToSAutomaton.size(), 70);

  for (const auto &[ea, ea_sa] : expectedToSAutomaton) {
    for (const auto &[ma, ma_sa] : minedToSAutomaton) {

      double similarity = computeEditDistanceSimilarity(ea_sa, ma_sa);
      //std::cout << "Similarity between " << ea->toString() << " and " << ma->toString() << " is " << similarity << "\n";
      report->_expextedToBestSimilarScore[ea->toString()] = std::max(
          similarity,
          report->_expextedToBestSimilarScore[ea->toString()]);
      pb.increment(0);
      pb.display();
    }
  }
  pb.done(0);
}

} // namespace usmt
