#include "Location.hh"
#include "UseCasePathHandler.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include <filesystem>
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
#include "temporalParsingUtils.hh"
#include "usmt-evaluator.hh"

//normal include
namespace usmt {
using namespace harm;

int compareLanguage(harm::AssertionPtr a1, harm::AssertionPtr a2) {
  //ret 0 if equivalent, 1 if a1 contains a2, 2 if a2 contains a1, -1 if not

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

int testEmpty(harm::AssertionPtr a1, harm::AssertionPtr a2) {
  //ret 0 if equivalent, 1 if a1 contains a2, 2 if a2 contains a1, -1 if not

  std::string a1_str = a1->toString(Language::SpotLTL);
  std::string a2_str = a2->toString(Language::SpotLTL);

  std::string test_formula = a1_str + " && !(" + a2_str + " )";
  spot::formula f = spot::parse_formula(test_formula);
  auto aut = generateDeterministicSpotAutomaton(f);

  int res = -1;

  if (aut->num_states() == 1) {
    res = 2;
  }

  test_formula = "!(" + a1_str + ") && " + a2_str;
  f = spot::parse_formula(test_formula);
  aut = generateDeterministicSpotAutomaton(f);

  if (aut->num_states() == 1) {
    if (res == 2) {
      res = 0;
    } else {
      res = 1;
    }
  }

  return res;
}

AssertionPtr makeAssertion(const std::string &ass_str,
                           const TracePtr &trace) {
  TemplateImplicationPtr ti = hparser::parseTemplateImplication(
      ass_str, trace, harm::DTLimits(), 0);
  messageErrorIf(!ti->assHoldsOnTrace(harm::Location::AntCon),
                 "Specification '" + ass_str +
                     "', does not hold on the input trace");
  AssertionPtr new_ass = generatePtr<Assertion>();
  fillAssertion(new_ass, ti, false);
  return new_ass;
}

std::vector<AssertionPtr>
parseAssertions(const std::vector<std::string> &assStrs,
                TracePtr trace) {

  std::vector<AssertionPtr> assertions;

  for (size_t i = 0; i < assStrs.size(); i++) {
    assertions.push_back(makeAssertion(assStrs[i], trace));
  }
  return assertions;
}

std::vector<AssertionPtr>
getAssertionsFromFile(const std::string &input_path,
                      const TracePtr &trace) {

  std::cout << "Parsing assertion file '" << input_path << "'";
  std::vector<std::string> assStrs;
  messageErrorIf(!std::filesystem::exists(input_path),
                 "Could not find assertino file'" + input_path + "'");
  std::fstream ass(input_path);

  std::string line = "";
  while (std::getline(ass, line)) {
    assStrs.push_back(line);
  }
  messageWarningIf(assStrs.empty(),
                   "No content found in assertion file '" +
                       input_path + "'");
  return parseAssertions(assStrs, trace);
}

using TraceReaderPtr = std::shared_ptr<TraceReader>;
TracePtr parseTrace(const usmt::UseCase &use_case,
                    const UseCasePathHandler &ph) {

  auto first_input = use_case.input[0];
  std::string trace_path =
      ph.ustm_root + "/input/" + first_input.path;

  std::cout << "Parsing " << trace_path << "\n";

  if (first_input.type == "vcd") {
    clc::selectedScope = use_case.input[0].scope;
    clc::vcdRecursive = 1;
    TraceReaderPtr tr =
        generatePtr<VCDtraceReader>(trace_path, first_input.clk);
    return tr->readTrace();
  } else if (first_input.type == "csv") {
    TraceReaderPtr tr = generatePtr<CSVtraceReader>(trace_path);
    return tr->readTrace();
  }
  messageError("Unsupported trace type");
  return nullptr;
}

EvalReport evaluate(const usmt::UseCasePathHandler &ph,
                    const usmt::UseCase &use_case,
                    const Comparator &comp) {
  if (comp.with_strategy == "expected_vs_mined") {
    return evaluateExpectedvsMined(
        ph, use_case, ph.ustm_root + "/input/" + comp.expected);
  }
  messageError("Unsupported strategy");
  return EvalReport();
}

EvalReport
evaluateExpectedvsMined(const usmt::UseCasePathHandler &ph,
                        const usmt::UseCase &use_case,
                        const std::string expected_ass_path) {

  std::cout << "Expected ass path " << expected_ass_path << "\n";
  TracePtr trace = parseTrace(use_case, ph);
  auto expected_ass = getAssertionsFromFile(expected_ass_path, trace);

  EvalReport ret;
  //clc::psilent = 1;
  double avgScore = 0.f;
  for (const auto &output : use_case.output) {
    std::string adapted_output_folder =
        ph.work_path + "adapted/" + output.path;
    auto mined_ass =
        getAssertionsFromFile(adapted_output_folder, trace);
    progresscpp::ParallelProgressBar pb;

    for (const auto &ea : expected_ass) {
      std::string expected_ass_str = ea->toString();
      pb.addInstance(0, "Comparing " + expected_ass_str,
                     mined_ass.size(), 70);
      double this_ass_score = 0.f;
      for (const auto &ma : mined_ass) {
        int res = compareLanguage(ea, ma);
        //std::cout << "-------->" <<res<< "\n";

        if (res == 0) {
          ret._expextedToSimilar[expected_ass_str].clear();
          ret._expextedToSimilar[expected_ass_str].push_back(
              ma->toString());
          this_ass_score = 1;
          pb.changeMessage(0, "Comparing " + expected_ass_str +
                                  " Covered!");
          pb.display();
          break;
        } else if (res != -1) {
          ret._expextedToSimilar[expected_ass_str].push_back(
              ma->toString());
        }
        pb.changeMessage(
            0,
            "Comparing " + expected_ass_str + " " +
                std::to_string(
                    ret._expextedToSimilar[expected_ass_str].size()));

        pb.increment(0);
        pb.display();
      }

      if (this_ass_score != 0.f) {
        this_ass_score =
            1.f / ret._expextedToSimilar.at(expected_ass_str).size();
      }
      avgScore += this_ass_score;
      pb.done(0);
    }
  }
  ret._score = avgScore / expected_ass.size();

  return ret;
}

} // namespace usmt
