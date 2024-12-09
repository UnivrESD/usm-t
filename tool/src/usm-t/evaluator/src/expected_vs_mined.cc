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

#include "Assertion.hh"
#include "CSVtraceReader.hh"
#include "EvalReport.hh"
#include "ProgressBar.hpp"
#include "Trace.hh"
#include "VCDtraceReader.hh"
#include "assertion_utils.hh"
#include "temporalParsingUtils.hh"
#include "usmt-evaluator.hh"

//normal include
namespace usmt {
using namespace harm;

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
  auto expected_ass =
      getAssertionsFromFile(expected_assertion_path, trace);

  ExpectedVSMinedReportPtr ret =
      std::make_shared<ExpectedVSMinedReport>();

  ret->_totExpected = expected_ass.size();

  for (const auto &output : use_case.output) {
    std::string adapted_output_folder =
        ph.work_path + "adapted/" + output.path;
    auto mined_ass =
        getAssertionsFromFile(adapted_output_folder, trace);
    progresscpp::ParallelProgressBar pb;

    for (const auto &ea : expected_ass) {
      std::string expected_assertion_str = ea->toString();
      pb.addInstance(0, "Comparing " + expected_assertion_str,
                     mined_ass.size(), 70);
      for (const auto &ma : mined_ass) {
        int res = compareLanguage(ea, ma);

        if (res == 0) {
          ret->_expectedCoveredWith.emplace_back(ea->toString(),
                                                 ma->toString());
          pb.changeMessage(0, "Comparing " + expected_assertion_str +
                                  " Covered!");
          pb.display();
          break;
        } else if (res != -1) {
          ret->_expextedToSimilar[ea->toString()].push_back(
              ma->toString());
        }
        size_t nOfSimilarAss =
            ret->_expextedToSimilar.count(expected_assertion_str)
                ? ret->_expextedToSimilar.at(expected_assertion_str)
                      .size()
                : 0;

        pb.changeMessage(0, "Comparing " + expected_assertion_str +
                                " " + std::to_string(nOfSimilarAss));
        pb.increment(0);
        pb.display();
      }

      pb.done(0);
    }
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

} // namespace usmt
