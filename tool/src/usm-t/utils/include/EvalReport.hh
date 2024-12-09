
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
  EvalReport() = default;
  ~EvalReport() {}
  virtual void dumpTo(const std::string &pathToDir) = 0;
  virtual std::string to_string() = 0;
};

class FaultCoverageReport : public EvalReport {

public:
  FaultCoverageReport() {}

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
  ExpectedVSMinedReport() {}
  ~ExpectedVSMinedReport() = default;

  virtual std::string to_string() override {
    std::stringstream ss;
    ss << "Expected vs Mined Report\n";
    ss << "Covered " << _expectedCoveredWith.size() << "/"
       << _totExpected << "\n";
    if (_expectedCoveredWith.size() != _totExpected) {
      ss << "Covered + Similar "
         << _expectedCoveredWith.size() + _expextedToSimilar.size()
         << "/" << _totExpected << "\n";
      ss << "--------Covered-"
         << "------------------\n";
    }

    for (const auto &pair : _expectedCoveredWith) {
      ss << pair.first << "\n";
      ss << "=>  \t\t" << pair.second << "\n";
    }
    if (_expectedCoveredWith.size() != _totExpected) {
      ss << "--------Similar "
         << "------------------\n";

      for (const auto &pair : _expextedToSimilar) {
        ss << pair.first << "\n";
        for (const auto &similar : pair.second) {
          ss << "\t\t\t->  " << similar << "\n";
        }
      }
    }

    ss << "----------------"
       << "------------------\n";

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
  std::vector<std::pair<std::string, std::string>>
      _expectedCoveredWith;
  size_t _totExpected = 0;
};

using EvalReportPtr = std::shared_ptr<EvalReport>;
using FaultCoverageReportPtr = std::shared_ptr<FaultCoverageReport>;
using ExpectedVSMinedReportPtr =
    std::shared_ptr<ExpectedVSMinedReport>;

} // namespace usmt
