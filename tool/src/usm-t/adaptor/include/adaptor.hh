#include <string>
#include <vector>

namespace usmt {
class Test;
class UseCasePathHandler;
class UseCase;

void adaptInput(const UseCasePathHandler &ph, const UseCase &use_case);
void adaptOutput(const UseCasePathHandler &ph, const UseCase &use_case);
} // namespace usmt
