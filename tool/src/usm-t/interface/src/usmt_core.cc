#include "PathHandler.hh"
#include "adaptor.hh"
#include "evaluator.hh"
#include "globals.hh"
#include "misc.hh"
#include "test_reader.hh"
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

    for (const auto &use_case : test.use_cases) {
      PathHandler ph = generatePaths(use_case);

      //ADAPT THE INPUT--------------------------------
      adaptInput(ph, use_case);

      //PREPARE THE EXECUTION-------------------------------
      //copy the conf input files to the input folder
      for (const auto &conf : use_case.configs) {
        if (conf.type == "input") {
          std::filesystem::copy(ph.configurations_path + conf.path,
                                ph.work_path + "input/");
        } else if (conf.type == "run") {
          messageErrorIf(std::filesystem::exists(
                             ph.work_path + "input/run_miner.sh"),
                         "Multiple run configurations not supported");
          std::filesystem::copy(ph.configurations_path + conf.path,
                                ph.work_path + "input/run_miner.sh");
        } else {
          messageError("Configuration type '" + conf.type +
                       "' not supported");
        }
      }

      //RUN THE MINER---------------------------------------
      std::string run_container_command = "";
      run_container_command = "bash " + ph.run_container_path;
      //add the shared input and output paths
      run_container_command += " " + ph.work_path + "input/";
      run_container_command += " " + ph.work_path + "output/";
      //add the command to be executed in the container
      run_container_command += " \"bash /input/run_miner.sh\"";
      messageInfo("Running '" + use_case.miner_name + "'");
      systemCustom(run_container_command);

      //ADAPT THE OUTPUT--------------------------------
      adaptOutput(ph, use_case);

      //EVAL-----------------------------------------------
      evaluate(ph, use_case);

    } //end of use cases
  }   //end of tests
}

} // namespace usmt
