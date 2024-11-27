#include "PathHandler.hh"
#include "message.hh"
#include "misc.hh"
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace usmt {
void adaptInput(const PathHandler &ph, const UseCase &use_case) {

  messageInfo("Adapting input...");
  std::string adapt_input_command = "bash " + ph.input_adaptor_path;
  //add the path to the input and output file of the input adaptor
  adapt_input_command +=
      " " + ph.ustm_root + "/input/" + use_case.input.path;
  adapt_input_command += " " + ph.work_path + "input/";

  systemCustom(adapt_input_command);
}
void adaptOutput(const PathHandler &ph, const UseCase &use_case) {

  messageInfo("Adapting output...");
  std::string adapt_output_command = "bash " + ph.output_adaptor_path;
  //add the path to the input and output file of the output adaptor
  adapt_output_command += " " + ph.work_ass;
  adapt_output_command +=
      " " + ph.work_path + ph.work_output + ph.adapted_ass_file;

  systemCustom(adapt_output_command);
}
} // namespace usmt
