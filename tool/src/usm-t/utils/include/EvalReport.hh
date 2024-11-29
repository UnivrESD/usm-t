
#pragma once
#include <string>

class EvalReport {
public:
  EvalReport(){};
  ~EvalReport() {}
  virtual std::string printReport() = 0;
};

class FaultCoverageReport : public EvalReport {

public:
  FaultCoverageReport() {}

  virtual ~FaultCoverageReport() = default;
  virtual std::string printReport() override{
    return "Fault Coverage: " + std::to_string(fault_coverage) + "\n";
  }

  double fault_coverage = 0.f;
};

class ExpectedVSMinedReport : public EvalReport {
public:
  ExpectedVSMinedReport() {}
  ~ExpectedVSMinedReport() = default;
};
