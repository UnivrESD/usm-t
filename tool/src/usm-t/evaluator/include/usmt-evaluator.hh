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
struct FlattenedAssertion;

int compareLanguage(const FlattenedAssertion &a1,
                    const FlattenedAssertion &a2);

EvalReportPtr
runSemanticEquivalence(const usmt::UseCase &use_case,
                       const std::string expected_assertion_path);

EvalReportPtr
runEditDistance(const usmt::UseCase &use_case,
                const std::string expected_assertion_path);

EvalReportPtr runFaultCoverage(const UseCase &use_case,
                                    const Comparator comp);

EvalReportPtr evaluate(const usmt::UseCase &use_case,
                       const Comparator &comp);

} // namespace usmt
