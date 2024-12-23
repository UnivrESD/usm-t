#include "Assertion.hh"
#include "EvalReport.hh"
#include "ProgressBar.hpp"
#include "TemplateImplication.hh"
#include "Test.hh"
#include "Trace.hh"
#include "assertion_utils.hh"
#include "globals.hh"
#include "misc.hh"
#include "set_cover/set_cover_wrapper.hh"
#include "temporalParsingUtils.hh"
#include "usmt-evaluator.hh"

#include <algorithm>
#include <random>

using namespace harm;

namespace usmt {

static void
usmt_fbqUsingFaultyTraces(const std::vector<AssertionPtr> &selected,
                          const TracePtr &originalTrace,
                          fault_coverage_t &fc_result);
struct fault_coverage_t {
  ///maps the assertion to the faults they cover
  std::unordered_map<size_t, std::vector<size_t>> _aidToF;
  ///maps covered faults to the assertion covering them
  std::unordered_map<size_t, std::vector<size_t>> _fToAid;
  //list of faulty traces
  std::vector<std::string> _faultyTraceFiles;
};

static std::vector<size_t>
getCoverageSet(const fault_coverage_t &fc_result);

EvalReportPtr runFaultCoverage(const UseCase &use_case,
                                    const Comparator comp) {

  FaultCoverageReportPtr ret = generatePtr<FaultCoverageReport>();

  const UseCasePathHandler &ph = use_case.ph;

  TracePtr trace = parseInputTraces(use_case);

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

  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(mined_assertions),
               std::end(mined_assertions), rng);

  fault_coverage_t fc_result;
  fc_result._faultyTraceFiles = recoverTracesInDirectory(
      use_case.ph.ustm_root + "/" + comp.faulty_traces,
      "." + comp.trace_type);
  ret->_totFaults = fc_result._faultyTraceFiles.size();

  clc::clk = use_case.input[0].clk;
  clc::parserType = comp.trace_type;
  clc::findMinSubset = 1;
  usmt_fbqUsingFaultyTraces(mined_assertions, trace, fc_result);
  std::unordered_map<size_t, std::vector<size_t>> &_fToAid =
      fc_result._fToAid;

  //gather info on the coverage

  ret->fault_coverage = (double)_fToAid.size() /
                        (double)fc_result._faultyTraceFiles.size();

  if (!_fToAid.empty()) {
    auto minCoveringAssertionsIds = getCoverageSet(fc_result);
    for (auto aid : minCoveringAssertionsIds) {
      //find the assertion that covers the fault
      auto found = std::find_if(
          mined_assertions.begin(), mined_assertions.end(),
          [aid](const AssertionPtr &a) { return a->_id == aid; });

      messageErrorIf(found == mined_assertions.end(),
                     "Assertion id '" + std::to_string(aid) +
                         "' not found in mined assertions");
      ret->_minCoveringAssertions.push_back((*found)->toString());
    }

    if (_fToAid.size() < fc_result._faultyTraceFiles.size()) {
      for (size_t j = 0; j < fc_result._faultyTraceFiles.size();
           j++) {
        if (!_fToAid.count(j)) {
          ret->_uncoveredFaults.push_back(
              fc_result._faultyTraceFiles[j]);
        }
      }
    }
  }

  return ret;
}

void usmt_fbqUsingFaultyTraces(
    const std::vector<AssertionPtr> &selected,
    const TracePtr &originalTrace, fault_coverage_t &fc_result) {

  std::unordered_map<size_t, std::vector<size_t>> &_aidToF =
      fc_result._aidToF;

  std::unordered_map<size_t, std::vector<size_t>> &_fToAid =
      fc_result._fToAid;

  //lower the number of threads to avoid wasting memory
  size_t prevl1Val = l1Constants::MAX_THREADS;
  l1Constants::MAX_THREADS = 1;

  progresscpp::ParallelProgressBar progressBarPS;
  progressBarPS.addInstance(0,
                            "Preparing fault-based qualification...",
                            selected.size(), 70);
  progressBarPS.display();
  std::unordered_map<size_t, TemplateImplicationPtr>
      aid_to_noCacheTemplates;

  //make a new template for each assertion to allow the use of templates utils
  for (const AssertionPtr &a : selected) {
    aid_to_noCacheTemplates[a->_id] =
        hparser::parseTemplateImplication(
            a->toString(), originalTrace, DTLimits(), 0);

    progressBarPS.increment(0);
    progressBarPS.display();
  }

  progressBarPS.done(0);

  //silence warnings and infos (to silence the traceReader)
  clc::isilent = 1;
  clc::wsilent = 1;

  progresscpp::ParallelProgressBar progressBar;
  progressBar.addInstance(
      0,
      "Fault coverage 0/" +
          std::to_string(fc_result._faultyTraceFiles.size()),
      selected.size() * fc_result._faultyTraceFiles.size(), 70);
  progressBar.display();

  for (size_t j = 0; j < fc_result._faultyTraceFiles.size(); j++) {
    //for each faulty trace

    progressBar.changeMessage(
        0, "Fault coverage " +
               (std::to_string(_fToAid.size()) + "/" +
                std::to_string(fc_result._faultyTraceFiles.size())) +
               " (" +
               to_string_with_precision(
                   (_fToAid.size() / (double)j) * 100.f, 2) +
               "%)" + " (Elaborating " +
               fc_result._faultyTraceFiles[j] + " [" +
               std::to_string(j + 1) + "])");

    auto ft = parseFaultyTrace(fc_result._faultyTraceFiles[j]);
    size_t elaborated = 0;
    for (auto [aid, noCacheTemplate] : aid_to_noCacheTemplates) {
      //test if the assertion fails on the faulty trace

      //new assertion with faulty trace
      TemplateImplicationPtr fAss =
          generatePtr<TemplateImplication>(*noCacheTemplate);
      fAss->changeTrace(ft);

      if (!fAss->assHoldsOnTrace(Location::AntCon)) {
        // new fault covered
        // store the assertion id that covers the fault
        _aidToF[aid].push_back(j);
        // store the fault that is covered by the assertion
        _fToAid[j].push_back(aid);
        if (!clc::findMinSubset) {
          //stop search for this fault if you do not want the optimal covering set
          //fill the progress bar with the remaining assertions not elaborated
          progressBar.increment(0, aid_to_noCacheTemplates.size() -
                                       elaborated);
          progressBar.display();

          break;
        }
      }

      progressBar.increment(0);
      progressBar.display();

      //keep track of the number of elaborated assertions (for the progress bar)
      elaborated++;
    }
  }

  // print last

  progressBar.changeMessage(
      0, "Fault coverage " +
             (std::to_string(_fToAid.size()) + "/" +
              std::to_string(fc_result._faultyTraceFiles.size())) +
             " (Elaborating " + fc_result._faultyTraceFiles.back() +
             " [" +
             std::to_string(fc_result._faultyTraceFiles.size()) +
             "])");

  progressBar.done(0);

  clc::isilent = 0;
  clc::wsilent = 0;

  //  debug
  //  which ass covers which fault?
  //for (auto aff : _aidToF) {
  //  std::cout << aff.first << ") " <<
  //  aff.first
  //            << "\n";
  //  for (auto f : aff.second) {
  //    std::cout << "\t"
  //              << "   " << f << "\n";
  //  }
  //}

  //deallocate the Templates created with only 1 thread
  aid_to_noCacheTemplates.clear();
  //restore the previous number of threads
  l1Constants::MAX_THREADS = prevl1Val;
}

std::vector<size_t>
getCoverageSet(const fault_coverage_t &fc_result) {

  const std::unordered_map<size_t, std::vector<size_t>> &_aidToF =
      fc_result._aidToF;

  std::vector<size_t> ret;
  if (_aidToF.empty()) {
    return ret;
  }

  std::vector<std::vector<int>> set_to_elements;
  std::unordered_map<int, int> setIdToAssId;
  size_t setId = 0;
  for (auto &[aID, fIDS] : _aidToF) {
    std::vector<int> cfSubset;
    for (auto fID : fIDS) {
      cfSubset.push_back(fID);
    }
    set_to_elements.push_back(cfSubset);
    setIdToAssId[setId] = aID;
    setId++;
  }
  auto selectedSets = findMinSetCover(set_to_elements);
  for (auto setId : selectedSets) {
    ret.push_back(setIdToAssId[setId]);
  }

  return ret;
}
} // namespace usmt

