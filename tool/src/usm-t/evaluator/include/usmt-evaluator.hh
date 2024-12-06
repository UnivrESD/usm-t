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
class Comparator;

int compareLanguage(harm::AssertionPtr a1, harm::AssertionPtr a2);
int testEmpty(harm::AssertionPtr a1, harm::AssertionPtr a2);

EvalReport
evaluateExpectedvsMined(const UseCasePathHandler &ph,
                        const UseCase &use_case,
                        const std::string expected_ass_path);

EvalReport evaluate(const usmt::UseCasePathHandler &ph,
                    const usmt::UseCase &use_case,
                    const Comparator &comp);

} // namespace usmt
