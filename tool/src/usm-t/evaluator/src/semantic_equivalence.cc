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
#include "FlattenedAssertion.hh"
#include "ProgressBar.hpp"
#include "Trace.hh"
#include "VCDtraceReader.hh"
#include "assertion_utils.hh"
#include "propositionParsingUtils.hh"
#include "temporalParsingUtils.hh"
#include "usmt-evaluator.hh"

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
      //no point in comparing if they have no common variables
      if (getNumberOfCommonVariables(fea.original, fma.original) ==
          0) {
        //std::cout << "Skipping " << fea.original->toString()
        //          << " and " << fma.original->toString()
        //          << " because they have no common variables\n";
        continue;
      }
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
    } //end for mined_assertions

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

  const std::string MINED_ASSERTIONS_FILE =
      getenv("MINED_ASSERTIONS_FILE");
  std::unordered_map<std::string, std::vector<FlattenedAssertion>>
      ret;

  //get assertions from file--------------------------------
  const UseCasePathHandler &ph = use_case.ph;
  TracePtr trace = parseInputTraces(use_case);
  auto expected_assertions =
      getAssertionsFromFile(expected_assertion_path, trace);
  messageErrorIf(expected_assertions.empty(),
                 "No expected assertions found in " +
                     expected_assertion_path);
  std::string adapted_output_folder =
      ph.work_path + "adapted/" + MINED_ASSERTIONS_FILE;
  auto mined_assertions =
      getAssertionsFromFile(adapted_output_folder, trace);

  //Flatten assertions--------------------------------------
  std::unordered_map<std::string, std::string>
      targetToRemap; //not used
  auto flattenedAssertions = getFlattenedAssertions(
      expected_assertions, mined_assertions, targetToRemap);

  evaluateWithSemanticComparison(report, flattenedAssertions);

  //compute final score
  report->_final_score += report->_expectedToCoveredWith.size();
  report->_final_score += report->_expectedToSimilar.size() * 0.1f;

  size_t totExpected = report->_expectedToCoveredWith.size() +
                       report->_expectedToSimilar.size() +
                       report->_uncovered.size();
  report->_final_score /= totExpected;

  report->_noise = (flattenedAssertions.at("mined").size() -
                    (report->_expectedToCoveredWith.size() +
                     report->_expectedToSimilar.size())) /
                   (double)flattenedAssertions.at("mined").size();

  return report;
}

} // namespace usmt
