#pragma once
#include "Assertion.hh"
#include <string>

namespace usmt {
struct FlattenedAssertion {
  FlattenedAssertion(const harm::AssertionPtr &original,
                     const std::string &flattened_str)
      : original(original), flattened_str(flattened_str) {}
  FlattenedAssertion() = default;
  harm::AssertionPtr original;
  std::string flattened_str;
};
} // namespace usmt
