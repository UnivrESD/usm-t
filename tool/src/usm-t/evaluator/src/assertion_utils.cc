
#include "usmt-evaluator.hh"

#include "Assertion.hh"
#include "CSVtraceReader.hh"
#include "EvalReport.hh"
#include "Location.hh"
#include "ProgressBar.hpp"
#include "Test.hh"
#include "Trace.hh"
#include "VCDtraceReader.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include "temporalParsingUtils.hh"
#include <algorithm>
#include <filesystem>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace harm;

namespace usmt {

AssertionPtr makeAssertion(const std::string &assertion_str,
                           const TracePtr &trace) {
  TemplateImplicationPtr ti = hparser::parseTemplateImplication(
      assertion_str, trace, harm::DTLimits(), 0);
  messageErrorIf(!ti->assHoldsOnTrace(harm::Location::AntCon),
                 "Specification '" + assertion_str +
                     "', does not hold on the input traces'");
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

  messageErrorIf(!std::filesystem::exists(input_path),
                 "Could not find assertino file'" + input_path + "'");
  messageInfo("Parsing assertion file '" + input_path);
  std::vector<std::string> assStrs;
  std::fstream ass(input_path);

  std::string line = "";
  while (std::getline(ass, line)) {
    assStrs.push_back(line);
  }
  messageErrorIf(assStrs.empty(),
                 "No content found in assertion file '" + input_path +
                     "'");
  return parseAssertions(assStrs, trace);
}

using TraceReaderPtr = std::shared_ptr<TraceReader>;
std::vector<std::string>
recoverTracesInDirectory(const std::string &path,
                         const std::string &extension) {
  messageErrorIf(!std::filesystem::exists(path),
                 "Could not find '" + path + "'");
  messageErrorIf(!std::filesystem::is_directory(path),
                 "Not a directory: '" + path + "'");
  std::vector<std::string> ret;
  for (const auto &entry :
       std::filesystem::directory_iterator(path)) {

    if (entry.path().extension() == extension) {
      ret.push_back(entry.path().u8string());
    }
  }
  return ret;
}

TracePtr parseInputTraces(const usmt::UseCase &use_case) {
  const UseCasePathHandler &ph = use_case.ph;

  std::string trace_prefix = ph.ustm_root + "/input/";

  std::vector<std::string> allTraces;

  for (const auto &input : use_case.input) {
    if (input.type != "vcd" && input.type != "csv") {
      continue;
    }
    std::string trace_path = trace_prefix + input.path;
    messageInfo("Parsing input trace(s) at " + trace_path);
    messageErrorIf(!std::filesystem::exists(trace_path),
                   "path '" + trace_path + "' does not exist");
    if (std::filesystem::is_directory(trace_path)) {
      auto traces_in_dir =
          recoverTracesInDirectory(trace_path, "." + input.type);
      allTraces.insert(allTraces.end(), traces_in_dir.begin(),
                       traces_in_dir.end());

    } else {

      allTraces.push_back(trace_path);
    }

    if (input.type == "vcd") {
      clc::selectedScope = use_case.input[0].scope;
      clc::vcdRecursive = 1;
      TraceReaderPtr tr =
          generatePtr<VCDtraceReader>(allTraces, input.clk);
      return tr->readTrace();
    } else if (input.type == "csv") {
      TraceReaderPtr tr = generatePtr<CSVtraceReader>(allTraces);
      return tr->readTrace();
    }
  }

  messageError("Unsupported trace type");
  return nullptr;
}

TracePtr parseFaultyTrace(const std::string &ftStr) {
  TraceReader *tr;
  if (clc::parserType == "vcd") {
    messageErrorIf(!std::filesystem::exists(ftStr),
                   "Can not find '" + ftStr + "'");
    tr = new VCDtraceReader(ftStr, clc::clk);
    TracePtr t = tr->readTrace();
    delete tr;
    return t;
  } else if (clc::parserType == "csv") {
    messageErrorIf(!std::filesystem::exists(ftStr),
                   "Can not find '" + ftStr + "'");
    tr = new CSVtraceReader(ftStr);
    TracePtr t = tr->readTrace();
    delete tr;
    return t;
  }
  messageError("Uknown parser type");
  return nullptr;
}
} // namespace usmt
