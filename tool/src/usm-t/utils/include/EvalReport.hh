
#pragma once
#include "message.hh"
#include <cstdio>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace usmt {

class EvalReport {
public:
  EvalReport(std::string with_strategy)
      : _with_strategy(with_strategy) {}
  ~EvalReport() {}
  virtual void dumpTo(const std::string &pathToDir) = 0;
  virtual std::string to_string() = 0;
  std::string _with_strategy;
};

class FaultCoverageReport : public EvalReport {

public:
  FaultCoverageReport() : EvalReport("fault_coverage") {}

  virtual ~FaultCoverageReport() = default;
  virtual std::string to_string() override {
    std::stringstream ss;
    ss << "Fault Coverage Report\n";

    ss << "Fault coverage: ";
    ss << "\t" << _totFaults - _uncoveredFaults.size() << "/"
       << _totFaults << " (" << fault_coverage * 100.f << "%)\n";

    if (_minCoveringAssertions.size() > 0) {
      ss << "Min covering set size: " << _minCoveringAssertions.size()
         << "\n";
      ss << "-------Min Covering Assertions----------\n";
      for (const auto &assertion : _minCoveringAssertions) {
        ss << "\t" << assertion << "\n";
      }
    }

    if (_uncoveredFaults.size() > 0) {
      ss << "---Uncovered Faults-------------------\n";
      for (const auto &fault : _uncoveredFaults) {
        ss << "\t" << fault << "\n";
      }
    }
    ss << "----------------------------------------\n";

    return ss.str();
  }

  virtual void dumpTo(const std::string &pathToDir) override {
    messageInfo("Dumping Fault Coverage Report to: " + pathToDir);
    std::ofstream out(pathToDir + "/fault_coverage_report.csv");
    out << "Fault covered, Covered %,  Min Covering Size, Min "
           "Covering Set\n";
    out << _totFaults - _uncoveredFaults.size() << ", "
        << fault_coverage * 100.f << ", "
        << _minCoveringAssertions.size() << ", ";
    for (const auto &assertion : _minCoveringAssertions) {
      out << assertion << " ";
    }
    out << "\n";
  }

  double fault_coverage = 0.f;
  std::vector<std::string> _uncoveredFaults;
  std::vector<std::string> _minCoveringAssertions;
  size_t _totFaults;
};

class ExpectedVSMinedReport : public EvalReport {
public:
  ExpectedVSMinedReport() : EvalReport("expected_vs_mined") {}
  ~ExpectedVSMinedReport() = default;

  virtual std::string to_string() override {
    std::stringstream ss;
    ss << "Expected vs Mined Report\n";
    ss << "Semantically Covered " << _expectedCoveredWith.size() << "/"
       << _totExpected << "\n";
    if (_expectedCoveredWith.size() != _totExpected) {
      ss << "SCovered + SSimilar "
         << _expectedCoveredWith.size() + _expextedToSimilar.size()
         << "/" << _totExpected << "\n";
      ss << "--------Covered-"
         << "------------------\n";
    }

    for (const auto &pair : _expectedCoveredWith) {
      ss << pair.first << "\n";
      ss << "--->  \t\t" << pair.second << "\n";
    }
    if (_expectedCoveredWith.size() != _totExpected) {
      ss << "--------Semantically Similar "
         << "------------------\n";

      for (const auto &pair : _expextedToSimilar) {
        ss << pair.first << "\n";
        for (const auto &similar : pair.second) {
          ss << "\t\t\t->  " << similar << "\n";
        }
      }
    }

    ss << "----------------Edit similarity------------------\n";
    for (const auto &pair : _expextedToBestSimilarScore) {
      ss << pair.first << " : " << pair.second << "\n";
    }


    return ss.str();
  }

  virtual void dumpTo(const std::string &pathToDir) override {
    messageInfo("Dumping Expected vs Mined Report to: " + pathToDir);
    std::ofstream out(pathToDir + "/expected_vs_mined_report.csv");
    out << "Expected, CoveredWith, Similar\n";
    for (const auto &pair : _expectedCoveredWith) {
      out << pair.first << ", " << pair.second << ", None \n";
    }
    for (const auto &pair : _expextedToSimilar) {
      for (const auto &similar : pair.second) {
        out << pair.first << ", None , " << similar << "\n";
      }
    }
  }

  double _score = 0.f;
  std::unordered_map<std::string, std::vector<std::string>>
      _expextedToSimilar;
  std::unordered_map<std::string, double> _expextedToBestSimilarScore;
  std::vector<std::pair<std::string, std::string>>
      _expectedCoveredWith;
  size_t _totExpected = 0;
};

class TemporalReport : public EvalReport {
public:
  TemporalReport() : EvalReport("time_to_mine") {}
  ~TemporalReport() = default;

  virtual std::string to_string() override {
    std::stringstream ss;
    ss << "Temporal Report\n";
    ss << "Time: " << (double)_timeMS / 1000.f << " ms\n";
    return ss.str();
  }

  virtual void dumpTo(const std::string &pathToDir) override {
    messageInfo("Dumping Temporal Report to: " + pathToDir);
    std::ofstream out(pathToDir + "/temporal_report.csv");
    out << "Time\n";
    out << (double)_timeMS / 1000.f << "\n";
  }

  size_t _timeMS = 0;
};

using EvalReportPtr = std::shared_ptr<EvalReport>;
using FaultCoverageReportPtr = std::shared_ptr<FaultCoverageReport>;
using ExpectedVSMinedReportPtr =
    std::shared_ptr<ExpectedVSMinedReport>;
using TemporalReportPtr = std::shared_ptr<TemporalReport>;

} // namespace usmt
