#include "EvalReport.hh"
#include "Test.hh"
#include "adaptor.hh"
#include "fort.h"
#include "fort.hpp"
#include "globals.hh"
#include "misc.hh"
#include "test_reader.hh"
#include "usmt-evaluator.hh"
#include "ustm_core.hh"
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <vector>

namespace usmt {

void run() {

  std::vector<Test> tests = readTestFile(clc::testFile);

  for (auto &test : tests) {
    messageInfo("Running test " + test.name);
    std::unordered_map<std::string, std::vector<EvalReportPtr>>
        evalReports;

    for (auto &use_case : test.use_cases) {
      initPathHandler(use_case);

      const UseCasePathHandler &ph = use_case.ph;

      //ADAPT THE INPUT--------------------------------
      adaptInput(use_case);

      //PREPARE THE EXECUTION-------------------------------
      //count number of run
      messageErrorIf(
          std::count_if(
              use_case.configs.begin(), use_case.configs.end(),
              [](const Config &c) { return c.type == "run"; }) != 1,
          "Multiple run configurations found in use case " +
              use_case.usecase_id);
      //copy the conf input files to the input folder
      for (const auto &conf : use_case.configs) {
        if (conf.type == "input") {
          std::filesystem::copy(ph.configurations_path + conf.path,
                                ph.work_path + "input/");
        } else if (conf.type == "run") {
          std::filesystem::copy(ph.configurations_path + conf.path,
                                ph.work_path + ph.work_input +
                                    "run_miner.sh");
        } else {
          messageError("Configuration type '" + conf.type +
                       "' not supported in '" + use_case.usecase_id +
                       "'");
        }
      }

      //RUN THE MINER---------------------------------------
      std::string run_container_command = "";
      run_container_command = "bash " + ph.run_container_path;
      //add the shared input and output paths
      run_container_command += " " + ph.work_path + ph.work_input;
      run_container_command += " " + ph.work_path + ph.work_output;
      //add the command to be executed in the container
      run_container_command += " \"bash /input/run_miner.sh\"";
      messageInfo("Running '" + use_case.miner_name + "'");

      //start the timer
      TemporalReportPtr tr = std::make_shared<TemporalReport>();
      auto start = std::chrono::high_resolution_clock::now();
      systemCheckExit(run_container_command);
      auto stop = std::chrono::high_resolution_clock::now();
      tr->_timeMS =
          std::chrono::duration_cast<std::chrono::milliseconds>(stop -
                                                                start)
              .count();
      evalReports[use_case.usecase_id].push_back(tr);

      //ADAPT THE OUTPUT--------------------------------
      adaptOutput(use_case);

      //EVAL-----------------------------------------------
      for (const auto &comp : test.comparators) {
        EvalReportPtr er = evaluate(use_case, comp);
        std::cout << er->to_string() << "\n";
        er->dumpTo(ph.work_path + ph.work_eval);
        evalReports[use_case.usecase_id].push_back(er);
      }
    } //end of use cases

    //AGGREGATE THE EVALUATION REPORTS-------------------
    fort::utf8_table table;
    table.set_border_style(FT_NICE_STYLE);

    table << fort::header << "Use case";
    table << "Time";
    for (const auto &comp : test.comparators) {
      table << comp.with_strategy;
    }
    table << fort::endr;

    for (const auto &[usecase_id, report] : evalReports) {
      std::vector<std::string> line;
      line.push_back(usecase_id);
      for (const auto &er : report) {
        //smart pointer cast
        if (std::dynamic_pointer_cast<FaultCoverageReport>(er)) {
          FaultCoverageReportPtr fcr =
              std::dynamic_pointer_cast<FaultCoverageReport>(er);
          line.push_back(
              to_string_with_precision(fcr->fault_coverage, 2));
        } else if (std::dynamic_pointer_cast<ExpectedVSMinedReport>(
                       er)) {
          ExpectedVSMinedReportPtr evmr =
              std::dynamic_pointer_cast<ExpectedVSMinedReport>(er);
          line.push_back(to_string_with_precision(evmr->_score, 2));
        } else if (std::dynamic_pointer_cast<TemporalReport>(er)) {
          TemporalReportPtr tr =
              std::dynamic_pointer_cast<TemporalReport>(er);
          line.push_back(to_string_with_precision(
                             (double)tr->_timeMS / 1000.f, 2) +
                         "s");
        } else {
          messageError("Unknown report type");
        }

      } //end of reports
      table.range_write_ln(std::begin(line), std::end(line));
    } // end of evalReports

    std::cout << table.to_string() << std::endl;
  } //end of tests
}

} // namespace usmt
