#include "Test.hh"
#include "message.hh"
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <sstream>

namespace usmt {
class PathHandler {
public:
  virtual ~PathHandler() = default;
  PathHandler(const UseCase &us) : us(us) {}

  std::string ustm_root = "";
  std::string miners_path = "";
  std::string miner_path = "";
  std::string tools_path = "";
  std::string work_input = "";
  std::string work_output = "";
  std::string work_eval = "";
  std::string work_path = "";
  std::string run_container_path = "";
  std::string expected_ass_file = "";
  std::string adapted_ass_file = "";
  std::string work_ass = "";

  std::string input_adaptor_path = "";
  std::string output_adaptor_path = "";
  std::string configurations_path = "";

private:
  const UseCase &us;
};

inline std::string getCurrentDateTime() {
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

inline PathHandler generatePaths(const UseCase &us) {

  PathHandler ret(us);

  messageErrorIf(getenv("USMT_ROOT") == nullptr,
                 "USTM_ROOT environment variable not set");

  ret.ustm_root = getenv("USMT_ROOT");
  ret.miners_path = ret.ustm_root + "/miners/";
  ret.tools_path = ret.miners_path + "tools/";
  ret.miner_path = ret.tools_path + us.miner_name + "/";
  ret.configurations_path = ret.miner_path + "configurations/";

  //--work folder
  ret.work_path =
      ret.miner_path + "runs/" + getCurrentDateTime() + "/";
  ret.work_input = "input/";
  ret.work_output = "output/";
  ret.work_eval = "eval/";

  //check if the work folder exists
  if (std::filesystem::exists(ret.work_path)) {
    //delete the folder
    std::filesystem::remove_all(ret.work_path);
  }

  //create the folder
  messageErrorIf(!std::filesystem::create_directories(ret.work_path),
                 "error while creating directory '" + ret.work_path +
                     "'");
  messageErrorIf(!std::filesystem::create_directories(ret.work_path +
                                                      ret.work_input),
                 "error while creating directory '" + ret.work_path +
                     ret.work_input + "'");
  messageErrorIf(!std::filesystem::create_directories(
                     ret.work_path + ret.work_output),
                 "error while creating directory '" + ret.work_path +
                     ret.work_output + "'");
  messageErrorIf(!std::filesystem::create_directories(ret.work_path +
                                                      ret.work_eval),
                 "error while creating directory '" + ret.work_path +
                     ret.work_eval + "'");

  //container
  ret.run_container_path =
      ret.tools_path + us.miner_name + "/docker/run_container.sh";
  messageErrorIf(!std::filesystem::exists(ret.run_container_path),
                 "Run container script not found");

  //output ass
  ret.expected_ass_file = "ass.txt";
  ret.adapted_ass_file = "adapted_ass.txt";
  ret.work_ass =
      ret.work_path + ret.work_output + ret.expected_ass_file;

  //adaptors
  ret.input_adaptor_path = ret.miners_path +
                           "adaptors/input_adaptors/" +
                           us.input_adaptor_path;

  ret.output_adaptor_path = ret.miners_path +
                            "adaptors/output_adaptors/" +
                            us.output_adaptor_path;
  return ret;
}

} // namespace usmt

