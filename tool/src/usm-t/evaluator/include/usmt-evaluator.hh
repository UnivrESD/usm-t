#include <memory>
#include <string>
#include <vector>

namespace harm {
class Assertion;
typedef std::shared_ptr<Assertion> AssertionPtr;
} // namespace harm

namespace usmt {
class PathHandler;
class UseCase;

int compareLanguage(harm::AssertionPtr a1, harm::AssertionPtr a2);
int testEmpty(harm::AssertionPtr a1, harm::AssertionPtr a2);

void evaluateExpectedvsMined(const PathHandler &ph,
                             const UseCase &use_case);

} // namespace usmt
