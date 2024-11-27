#include <string>
#include <vector>

namespace usmt {
class Test;
class PathHandler;
class UseCase;

void adaptInput(const PathHandler &ph, const UseCase &use_case);
void adaptOutput(const PathHandler &ph, const UseCase &use_case);
} // namespace usmt
