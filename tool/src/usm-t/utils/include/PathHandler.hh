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
  //check that miners_path exists
  messageErrorIf(!std::filesystem::exists(ret.miners_path),
                 "Could not find miners path '" + ret.miners_path +
                     "'");
  ret.tools_path = ret.miners_path + "tools/";
  messageErrorIf(!std::filesystem::exists(ret.tools_path),
                 "Could not find tools path '" + ret.tools_path +
                     "'");
  ret.miner_path = ret.tools_path + us.miner_name + "/";
  messageErrorIf(!std::filesystem::exists(ret.miner_path),
                 "Could not find miner path '" + ret.miner_path +
                     "'");
  ret.configurations_path = ret.miner_path + "configurations/";
  messageErrorIf(!std::filesystem::exists(ret.configurations_path),
                 "Could not find configurations path '" +
                     ret.configurations_path + "'");

  //--work folder
  ret.work_path =
      ret.miner_path + "runs/" + getCurrentDateTime() + "/";
  //check if the work folder exists
  if (std::filesystem::exists(ret.work_path)) {
    //delete the folder
    std::filesystem::remove_all(ret.work_path);
  }

  ret.work_input = "input/";
  ret.work_output = "output/";
  ret.work_eval = "eval/";

  //create the folders
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
                 "Run container script '" + ret.run_container_path +
                     "' not found");

  //adaptors
  ret.input_adaptor_path = ret.miners_path +
                           "adaptors/input_adaptors/" +
                           us.input_adaptor_path;
  messageErrorIf(!std::filesystem::exists(ret.input_adaptor_path),
                 "Input adaptor '" + ret.input_adaptor_path +
                     "' not found");

  ret.output_adaptor_path = ret.miners_path +
                            "adaptors/output_adaptors/" +
                            us.output_adaptor_path;
  messageErrorIf(!std::filesystem::exists(ret.output_adaptor_path),
                 "Output adaptor '" + ret.output_adaptor_path +
                     "' not found");
  return ret;
}

} // namespace usmt

