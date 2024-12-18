#include <memory>
#include <string>
#include <vector>

namespace harm {
class Assertion;
typedef std::shared_ptr<Assertion> AssertionPtr;
} // namespace harm

namespace usmt {
class UseCasePathHandler;
class UseCase;
class EvalReport;
using EvalReportPtr = std::shared_ptr<EvalReport>;
class Comparator;
struct fault_coverage_t;

int compareLanguage(harm::AssertionPtr a1, harm::AssertionPtr a2);

EvalReportPtr
evaluateExpectedvsMined(const UseCase &use_case,
                        const std::string expected_ass_path);

EvalReportPtr evaluateFaultCoverage(const UseCase &use_case,
                                    const Comparator comp);

EvalReportPtr evaluate(const usmt::UseCase &use_case,
                       const Comparator &comp);

} // namespace usmt
