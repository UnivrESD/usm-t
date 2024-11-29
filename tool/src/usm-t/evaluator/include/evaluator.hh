#include <string>
#include <vector>

namespace usmt {
class PathHandler;
class UseCase;

float semanticComparison(std::string a1, std::string a2);

void evaluateExpectedvsMined(const PathHandler &ph, const UseCase &use_case);



} // namespace usmt
