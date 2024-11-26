#include <filesystem>
#include <iostream>
#include <memory>
#include <ostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "commandLineParser.hh"
#include "globals.hh"
#include "message.hh"
#include "misc.hh"
#include "ustm_core.hh"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace usmt;

/// @brief handle all the command line arguments
static void parseCommandLineArguments(int argc, char *args[]);

int main(int arg, char *argv[]) {

  //enforce deterministic rand
  srand(1);

  //print welcome message
  //std::cout << getIcon() << "\n";

  parseCommandLineArguments(arg, argv);

  run();

  return 0;
}

void parseCommandLineArguments(int argc, char *args[]) {
  //parse the cmd using an external library
  auto result = parseHARM(argc, args);

  //check for errors and build the environment
  //messageErrorIf(((result.count("vcd") || result.count("vcd-dir")) &&
  //                (result.count("csv") || result.count("csv-dir"))),
  //               "Mixing vcd with csv traces");

  if (result.count("name")) {
    hs::name = result["name"].as<std::string>();
  }

  ////------------------------
  ////vcd cases
  ////vcd-ss or vcd-ss + vcd-r == 0 : get signals only in selected scope
  ////vcd-ss + vcd-r = n with n>0 : get signals in selected scope and recursive with depth n
  ////vcd-ss + vcd-unroll = n with n>0 : get signals in selected scope and recursive with depth n and make a context for each scope
  //if (result.count("vcd-ss")) {
  //  clc::selectedScope = result["vcd-ss"].as<std::string>();
  //  clc::vcdRecursive = 0;
  //}
  //if (result.count("vcd-r")) {
  //  clc::vcdRecursive = safeStoull(result["vcd-r"].as<std::string>());
  //}

  //messageErrorIf(result.count("vcd-unroll") &&
  //                   (result.count("vcd-r")),
  //               "Can not use 'vcd-unroll' with 'vcd-r'");

  //messageErrorIf(
  //    result.count("vcd-unroll") && !result.count("generate-config"),
  //    "Can not use 'vcd-unroll' without 'generate-config'");

  //if (result.count("vcd-unroll")) {
  //  clc::vcdUnroll =
  //      safeStoull(result["vcd-unroll"].as<std::string>());
  //  messageErrorIf(clc::vcdUnroll == 0,
  //                 "vcd-unroll must be greater than 0");
  //}

  //if (result.count("clk")) {
  //  clc::clk = result["clk"].as<std::string>();
  //}

  //if (result.count("vcd")) {
  //  clc::parserType = "vcd";
  //  clc::traceFiles.push_back(result["vcd"].as<std::string>());
  //  messageErrorIf(!std::filesystem::exists(clc::traceFiles[0]),
  //                 "Can not find trace file '" + clc::traceFiles[0] +
  //                     "'");
  //} else if (result.count("csv")) {
  //  clc::parserType = "csv";
  //  clc::traceFiles.push_back(result["csv"].as<std::string>());
  //  messageErrorIf(!std::filesystem::exists(clc::traceFiles[0]),
  //                 "Can not find trace file '" + clc::traceFiles[0] +
  //                     "'");
  //}

  //if (result.count("vcd-dir")) {
  //  clc::parserType = "vcd";
  //  messageErrorIf(!std::filesystem::is_directory(
  //                     result["vcd-dir"].as<std::string>()),
  //                 "Can not find directory '" +
  //                     result["vcd-dir"].as<std::string>() + "'");
  //  for (const auto &entry : std::filesystem::directory_iterator(
  //           result["vcd-dir"].as<std::string>())) {
  //    if (entry.path().extension() == ".vcd") {
  //      clc::traceFiles.push_back(entry.path().u8string());
  //    }
  //  }
  //  messageErrorIf(clc::traceFiles.empty(),
  //                 "No vcd trace found in: " +
  //                     result["vcd-dir"].as<std::string>());
  //} else if (result.count("csv-dir")) {
  //  messageErrorIf(!std::filesystem::is_directory(
  //                     result["csv-dir"].as<std::string>()),
  //                 "Can not find directory '" +
  //                     result["csv-dir"].as<std::string>() + "'");
  //  for (const auto &entry : std::filesystem::directory_iterator(
  //           result["csv-dir"].as<std::string>())) {
  //    clc::parserType = "csv";
  //    if (entry.path().extension() == ".csv") {
  //      clc::traceFiles.push_back(entry.path().u8string());
  //    }
  //  }
  //  messageErrorIf(clc::traceFiles.empty(),
  //                 "No csv trace found in: " +
  //                     result["csv_dir"].as<std::string>());
  //}

  //if (result.count("sva")) {
  //  messageErrorIf(
  //      result.count("spotltl") || result.count("psl"),
  //      "sva and spotltl/psl options are mutually exclusive");
  //  clc::outputLang = Language::SVA;
  //}

  //if (result.count("sva-assert")) {
  //  messageErrorIf(result.count("spotltl") || result.count("psl"),
  //                 "sva-assert available only with --sva");
  //  clc::svaAssert = true;
  //}

  //if (result.count("psl")) {
  //  messageErrorIf(
  //      result.count("spotltl") || result.count("sva"),
  //      "psl and spotltl/sva options are mutually exclusive");
  //  clc::outputLang = Language::PSL;
  //}

  //if (result.count("spotltl")) {
  //  messageErrorIf(
  //      result.count("psl") || result.count("sva"),
  //      "spotltl and psl/sva options are mutually exclusive");
  //  clc::outputLang = Language::SpotLTL;
  //}

  clc::testFile = result["test"].as<std::string>();

  messageErrorIf(!std::filesystem::exists(clc::testFile),
                 "Can not find config file '" + clc::testFile + "'");
  //check that config file is an xml file
  messageErrorIf(clc::testFile.find(".xml") == std::string::npos,
                 "Config file must be an xml file, got '" +
                     clc::testFile + "'");
  messageInfo("Using test file: " + clc::testFile);

  //if (result.count("max-ass")) {
  //  clc::maxAss = result["max-ass"].as<size_t>();
  //}

  if (result.count("max-threads")) {
    size_t nt = result["max-threads"].as<size_t>();
    messageErrorIf(nt == 0, "max-threads must be > 0 ");
    messageWarningIf(
        nt > std::thread::hardware_concurrency(),
        "This machine should run " +
            std::to_string(std::thread::hardware_concurrency()) +
            " threads at most");

    clc::maxThreads = nt;
    l3Constants::MAX_THREADS = nt;
    l2Constants::MAX_THREADS = nt;
    l1Constants::MAX_THREADS = nt;
  }

  //if (result.count("fd")) {
  //  if (clc::parserType == "vcd") {
  //    for (const auto &entry : std::filesystem::directory_iterator(
  //             result["fd"].as<std::string>())) {
  //      if (entry.path().extension() == ".vcd") {
  //        clc::faultyTraceFiles.push_back(entry.path().u8string());
  //      }
  //    }
  //    //shuffle the faulty traces, to have an immediate potential outlook on the whole fault coverage
  //    std::random_shuffle(clc::faultyTraceFiles.begin(),
  //                        clc::faultyTraceFiles.end());

  //  } else if (clc::parserType == "csv") {
  //    for (const auto &entry : std::filesystem::directory_iterator(
  //             result["fd"].as<std::string>())) {
  //      if (entry.path().extension() == ".csv") {
  //        clc::faultyTraceFiles.push_back(entry.path().u8string());
  //      }
  //    }
  //  }
  //}

  //messageErrorIf(result.count("ftm") && result.count("fd"),
  //               "ftm and fd options are mutually exclusive");

  if (result.count("silent")) {
    clc::silent = true;
    // disable cout
    std::cout.rdbuf(NULL);
  }
  if (result.count("isilent")) {
    clc::isilent = true;
  }
  if (result.count("wsilent")) {
    clc::wsilent = true;
  }
  if (result.count("psilent")) {
    clc::psilent = true;
  }

  if (result.count("dump-stat")) {
    clc::dumpStat = true;
  }

  if (result.count("dump-to")) {
    clc::dumpAssToFile = true;
    clc::dumpPath = result["dump-to"].as<std::string>();
    messageErrorIf(clc::dumpPath.back() == '/' &&
                       !std::filesystem::exists(clc::dumpPath),
                   "Can not find directory path '" + clc::dumpPath +
                       "'");
    clc::dumpAssSplitContexts =
        std::filesystem::is_directory(clc::dumpPath);

    if (!clc::dumpAssSplitContexts &&
        std::filesystem::exists(clc::dumpPath)) {
      std::filesystem::remove(clc::dumpPath);
      std::ofstream fs(clc::dumpPath);
      fs.close();
    }
  }
}
