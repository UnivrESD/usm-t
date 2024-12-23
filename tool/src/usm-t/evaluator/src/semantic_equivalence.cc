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

#include "FlattenedAssertion.hh"
#include "z3CheckSat.hh"

//normal include

namespace usmt {
using namespace harm;

static std::map<std::pair<std::string, std::string>, bool>
    non_bool_prop_cache;

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
      if (non_bool_prop_cache.count(std::make_pair(rt1, rt2))) {
        p1_implies_p2 =
            non_bool_prop_cache.at(std::make_pair(rt1, rt2));
      } else {
        p1_implies_p2 = z3::check_implies(p1, p2);
        non_bool_prop_cache[std::make_pair(rt1, rt2)] = p1_implies_p2;
      }
      if (non_bool_prop_cache.count(std::make_pair(rt2, rt1))) {
        p2_implies_p1 =
            non_bool_prop_cache.at(std::make_pair(rt2, rt1));
      } else {
        p2_implies_p1 = z3::check_implies(p2, p1);
        non_bool_prop_cache[std::make_pair(rt2, rt1)] = p2_implies_p1;
      }

      if (p1_implies_p2 && p2_implies_p1) {
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

void evaluateWithSemanticComparison(
    SemanticEquivalenceReportPtr report,
    const std::unordered_map<std::string,
                             std::vector<FlattenedAssertion>>
        &flattenedAssertions) {

  progresscpp::ParallelProgressBar pb;

  const std::vector<FlattenedAssertion> &expected_assertions =
      flattenedAssertions.at("expected");

  const std::vector<FlattenedAssertion> &mined_assertions =
      flattenedAssertions.at("mined");

  pb.addInstance(0, "Semantic Matching...",
                 expected_assertions.size(), 70);

  for (const auto &fea : expected_assertions) {
    std::string fea_assertionStr = fea.original->toString();
    if (report->_expectedToCoveredWith.count(fea_assertionStr)) {
      goto increment_pb;
    }
    for (const auto &fma : mined_assertions) {
      int res = compareLanguage(fea, fma);
      std::string fma_assertionStr = fma.original->toString();

      if (res == 0) {
        report->_expectedToCoveredWith[fea_assertionStr] =
            fma_assertionStr;
        //clear the similar ones if they are present
        if (report->_expectedToSimilar.count(fea_assertionStr)) {
          report->_expectedToSimilar.erase(fea_assertionStr);
        }
        goto increment_pb;
      } else if (res != -1) {
        report->_expectedToSimilar[fea.original->toString()].insert(
            fma_assertionStr);
      }
    }
    if (!report->_expectedToSimilar.count(fea_assertionStr)) {
      report->_uncovered.push_back(fea_assertionStr);
    }

  increment_pb:
    pb.increment(0);
    pb.display();
  }
  pb.done(0);
}

EvalReportPtr
runSemanticEquivalence(const usmt::UseCase &use_case,
                       const std::string expected_assertion_path) {

  SemanticEquivalenceReportPtr report =
      std::make_shared<SemanticEquivalenceReport>();

  auto flattenedAssertions =
      getFlattenedAssertions(use_case, expected_assertion_path);

  for (const auto &output : use_case.output) {
    evaluateWithSemanticComparison(report, flattenedAssertions);
  }

  //compute final score
  for (const auto &[ea, coveredWith] :
       report->_expectedToCoveredWith) {
    report->_final_score += 1.f;
  }
  for (const auto &[ea, similar] : report->_expectedToSimilar) {
    report->_final_score += 0.5f;
  }

  size_t totExpected = report->_expectedToCoveredWith.size() +
                       report->_expectedToSimilar.size() +
                       report->_uncovered.size();
  report->_final_score /= totExpected;

  return report;
}

} // namespace usmt
