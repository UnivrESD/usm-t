
#include "usmt-evaluator.hh"
#include "Test.hh"
#include "message.hh"

namespace usmt {
EvalReportPtr evaluate(const usmt::UseCase &use_case,
                       const Comparator &comp) {

  const UseCasePathHandler &ph = use_case.ph;

  if (comp.with_strategy == "expected_vs_mined") {
    return evaluateExpectedvsMined(use_case, ph.ustm_root + "/" +
                                                 comp.expected);
  } else if (comp.with_strategy == "fault_coverage") {
    return evaluateFaultCoverage(use_case, comp);
  }

  messageError("Unsupported strategy '" + comp.with_strategy + "'");
  return {};
}
} // namespace usmt
