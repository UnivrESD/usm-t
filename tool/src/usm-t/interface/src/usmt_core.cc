#include "Test.hh"
#include "globals.hh"
#include "misc.hh"
#include "test_reader.hh"
#include "ustm_core.hh"
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>

namespace usmt {
std::string getCurrentDateTime() {
  // Get current system time
  auto now = std::chrono::system_clock::now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);

  // Convert to local time
  struct tm *local_time = std::localtime(&now_c);

  // Use stringstream to format the date and time
  std::stringstream ss;
  ss << std::put_time(local_time, "%m-%d-%Y_%H-%M");

  // Return the formatted string
  return ss.str();
}

void run() {
  //get environment variab USTM_ROOT
  messageErrorIf(getenv("USMT_ROOT") == nullptr,
                 "USTM_ROOT environment variable not set");
  std::string ustm_root = getenv("USMT_ROOT");
  std::string miners_path = ustm_root + "/miners/";
  std::string tools_path = miners_path + "tools/";

  std::vector<Test> tests = readTestFile(clc::testFile);

  for (auto &test : tests) {
    messageInfo("Running test " + test.name);
    for (const auto &use_case : test.use_cases) {
      //generate run
      //get day and time to create a unique folder
      std::string folder_path = tools_path + use_case.miner_name +
                                "/runs/" + getCurrentDateTime() + "/";
      //check if the folder exists
      if (std::filesystem::exists(folder_path)) {
        //delete the folder
        std::filesystem::remove_all(folder_path);
      }

      //create the folder
      messageErrorIf(
          !std::filesystem::create_directories(folder_path),
          "error while creating directory '" + folder_path + "'");
      messageErrorIf(
          !std::filesystem::create_directories(folder_path + "input"),
          "error while creating directory '" + folder_path +
              "input'");
      messageErrorIf(!std::filesystem::create_directories(
                         folder_path + "output"),
                     "error while creating directory '" +
                         folder_path + "output'");
      messageErrorIf(
          !std::filesystem::create_directories(folder_path + "eval"),
          "error while creating directory '" + folder_path + "eval'");

      //adapt the input
      std::string adapt_input_command = "bash " + miners_path +
                                        "adaptors/input_adaptors/" +
                                        use_case.input_adaptor_path;
      adapt_input_command +=
          " " + ustm_root + "/input/" + use_case.input.path;
      adapt_input_command += " " + folder_path + "input/";
      //run the script to adapt the input
      systemCustom(adapt_input_command);

      //copy the conf input files to the input folder
      for (const auto &conf : use_case.configs) {
        //extract the configuration file path wihtout the prefix
        if (conf.type == "input") {
          std::filesystem::copy(tools_path + use_case.miner_name +
                                    "/configurations/" + conf.path,
                                folder_path + "input/");
        } else if (conf.type == "run") {
          messageErrorIf(std::filesystem::exists(
                             folder_path + "input/run_miner.sh"),
                         "Multiple run configurations not supported");
          std::filesystem::copy(tools_path + use_case.miner_name +
                                    "/configurations/" + conf.path,
                                folder_path + "input/run_miner.sh");
        } else {
          messageError("Configuration type '" + conf.type +
                       "' not supported");
        }
      }

      std::string run_container_path = tools_path +
                                       use_case.miner_name +
                                       "/docker/run_container.sh";
      std::string run_command = "";
      run_command = "bash " + run_container_path + " " + folder_path +
                    "input/" + " " + folder_path + "output/" +
                    " \"bash /input/run_miner.sh\"";

      //run the miner
      systemCustom(run_command);
    } //end of use cases
  }   //end of tests
}

} // namespace usmt
