#pragma once
#include "Assertion.hh"
#include <string>

namespace usmt {
struct FlattenedAssertion {
  harm::AssertionPtr original;
  std::string flattened_str;
};
} // namespace usmt
