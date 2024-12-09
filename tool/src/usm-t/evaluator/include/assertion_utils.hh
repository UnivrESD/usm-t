#pragma once
#include <memory>
#include <vector>

namespace harm {
class Assertion;
using AssertionPtr = std::shared_ptr<Assertion>;

class Trace;
using TracePtr = std::shared_ptr<Trace>;
} // namespace harm

namespace usmt {
class UseCase;

harm::AssertionPtr makeAssertion(const std::string &assertion_str,
                                 const harm::TracePtr &trace);

std::vector<harm::AssertionPtr>
parseAssertions(const std::vector<std::string> &assStrs,
                harm::TracePtr trace);

std::vector<harm::AssertionPtr>
getAssertionsFromFile(const std::string &input_path,
                      const harm::TracePtr &trace);

harm::TracePtr parseInputTraces(const usmt::UseCase &use_case);
harm::TracePtr parseFaultyTrace(const std::string &ftStr);

std::vector<std::string>
recoverTracesInDirectory(const std::string &path,
                         const std::string &extension);
} // namespace usmt
