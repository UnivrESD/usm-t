
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace usmt {
struct EvalReport {

  std::string _type = "";
  double _score = 0.f;
  std::unordered_map<std::string, std::vector<std::string>>
      _expextedToSimilar;
};

} // namespace usmt
