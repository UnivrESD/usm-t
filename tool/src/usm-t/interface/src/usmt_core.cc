#include "EvalReport.hh"
#include "Test.hh"
#include "adaptor.hh"
#include "globals.hh"
#include "misc.hh"
#include "test_reader.hh"
#include "usmt-evaluator.hh"
#include "ustm_core.hh"
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>

namespace usmt {
void run() {

  std::vector<Test> tests = readTestFile(clc::testFile);

  for (auto &test : tests) {
    messageInfo("Running test " + test.name);

    for (auto &use_case : test.use_cases) {
      initPathHandler(use_case);

      const UseCasePathHandler &ph = use_case.ph;

      //ADAPT THE INPUT--------------------------------
      adaptInput(use_case);

      //PREPARE THE EXECUTION-------------------------------
      //copy the conf input files to the input folder
      for (const auto &conf : use_case.configs) {
        if (conf.type == "input") {
          std::filesystem::copy(ph.configurations_path + conf.path,
                                ph.work_path + "input/");
        } else if (conf.type == "run") {
          std::filesystem::copy(ph.configurations_path + conf.path,
                                ph.work_path + "input/run_miner.sh");
        } else {
          messageError("Configuration type '" + conf.type +
                       "' not supported in '" + use_case.usecase_id +
                       "'");
        }
      }

      //count number of run
      messageErrorIf(
          std::count_if(
              use_case.configs.begin(), use_case.configs.end(),
              [](const Config &c) { return c.type == "run"; }) != 1,
          "Multiple run configurations found in use case " +
              use_case.usecase_id);

      //RUN THE MINER---------------------------------------
      std::string run_container_command = "";
      run_container_command = "bash " + ph.run_container_path;
      //add the shared input and output paths
      run_container_command += " " + ph.work_path + "input/";
      run_container_command += " " + ph.work_path + "output/";
      //add the command to be executed in the container
      run_container_command += " \"bash /input/run_miner.sh\"";
      messageInfo("Running '" + use_case.miner_name + "'");
      systemCheckExit(run_container_command);

      //ADAPT THE OUTPUT--------------------------------
      adaptOutput(use_case);

      //EVAL-----------------------------------------------
      for (const auto &comp : test.comparators) {
        EvalReport er = evaluate(use_case, comp);
        std::cout << er._score << "\n";
        for (auto &[ex, sim] : er._expextedToSimilar) {
          std::cout << "Ex: " << ex << "\n";
          for (auto &s : sim) {
            std::cout << "\t\t\tSim: " << s << "\n";
          }
        }
      }

    } //end of use cases
  }   //end of tests
}

} // namespace usmt
