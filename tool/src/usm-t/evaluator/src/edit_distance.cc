#include "Assertion.hh"
#include "AutomataBasedEvaluator.hh"
#include "EvalReport.hh"
#include "ProgressBar.hpp"
#include "Test.hh"
#include "assertion_utils.hh"
#include "gedlibWrapper.hh"
#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace usmt {
using namespace harm;

std::unordered_map<std::string, std::vector<AssertionPtr>>
getAssertions(const usmt::UseCase &use_case,
              const std::string expected_assertion_path) {
  std::unordered_map<std::string, std::vector<AssertionPtr>> ret;

  const UseCasePathHandler &ph = use_case.ph;
  TracePtr trace = parseInputTraces(use_case);
  auto expected_assertions =
      getAssertionsFromFile(expected_assertion_path, trace);
  messageErrorIf(expected_assertions.empty(),
                 "No expected assertions found in " +
                     expected_assertion_path);
  ret["expected"] = expected_assertions;

  std::vector<AssertionPtr> mined_assertions;
  for (const auto &output : use_case.output) {
    std::string adapted_output_folder =
        ph.work_path + "adapted/" + output.path;
    auto mined_assertions_tmp =
        getAssertionsFromFile(adapted_output_folder, trace);
    mined_assertions.insert(mined_assertions.end(),
                            mined_assertions_tmp.begin(),
                            mined_assertions_tmp.end());
  }
  ret["mined"] = mined_assertions;

  return ret;
}

void evaluateWithEditDistance(
    EditDistanceReportPtr &report,
    const std::unordered_map<std::string, std::vector<AssertionPtr>>
        &assertions) {

  std::unordered_map<AssertionPtr, SerializedAutomaton>
      expectedToSAutomaton;

  std::unordered_map<AssertionPtr, SerializedAutomaton>
      minedToSAutomaton;

  const std::vector<AssertionPtr> &expectedAssertions =
      assertions.at("expected");
  const std::vector<AssertionPtr> &minedAssertions =
      assertions.at("mined");

  for (const auto &ea : expectedAssertions) {
    //Extract the automaton without the G
    Automaton *aut =
        //generateAutomatonFromTemporal(ea->_formula->getItems()[0]);
        generateAutomatonFromTemporal(ea->_formula);
    expectedToSAutomaton[ea] = serializeAutomaton(aut);
  }

  for (const auto &ma : minedAssertions) {
    //Extract the automaton without the G
    Automaton *aut =
        //generateAutomatonFromTemporal(ma->_formula->getItems()[0]);
        generateAutomatonFromTemporal(ma->_formula);
    minedToSAutomaton[ma] = serializeAutomaton(aut);
  }

  progresscpp::ParallelProgressBar pb;
  pb.addInstance(0, "Computing Edit Distance Similarity...",
                 expectedToSAutomaton.size(), 70);

  for (const auto &[ea, ea_sa] : expectedToSAutomaton) {
    std::string ea_assertionStr = ea->toString();
    for (const auto &[ma, ma_sa] : minedToSAutomaton) {
      std::string ma_assertionStr = ma->toString();

      double similarity = computeEditDistanceSimilarity(ea_sa, ma_sa);
      //std::cout << "Similarity between " << ea->toString() << " and " << ma->toString() << " is " << similarity << "\n";
      if (similarity >=
          report->_expectedToClosest[ea_assertionStr].second) {
        report->_expectedToClosest[ea_assertionStr] =
            std::make_pair(ma_assertionStr, similarity);
      }
      if (similarity == 1.f) {
        break;
      }
    }
    pb.increment(0);
    pb.display();
  }
  pb.done(0);
}

EvalReportPtr
runEditDistance(const usmt::UseCase &use_case,
                const std::string expected_assertion_path) {

  EditDistanceReportPtr report =
      std::make_shared<EditDistanceReport>();

  std::unordered_map<std::string, std::vector<AssertionPtr>>
      assertions = getAssertions(use_case, expected_assertion_path);

  for (const auto &output : use_case.output) {
    evaluateWithEditDistance(report, assertions);
  }

  //compute final score
  for (const auto &[ea, closest] : report->_expectedToClosest) {
    auto &[closest_str, sim] = closest;
    report->_final_score += sim;
  }

  report->_final_score /= report->_expectedToClosest.size();

  return report;
}

} // namespace usmt
