#include <string>
#include <vector>

#include "UseCasePathHandler.hh"

namespace usmt {

struct Input {
  std::string type;
  std::string rst;
  std::string path;
  std::string clk;
  std::string scope;
};
struct Output {
  std::string path;
};

struct Config {
  std::string type;
  std::string path;
};

struct UseCase {
  std::string usecase_id;
  std::string miner_name;
  std::vector<Input> input;
  std::vector<Output> output;
  std::vector<Config> configs;
  std::string input_adaptor_path;
  std::string output_adaptor_path;

  UseCasePathHandler ph;
};

struct Comparator {
  std::string with_strategy;
  std::string expected;
  std::string faulty_traces;
  std::string trace_type;
};

struct Test {
  std::vector<UseCase> use_cases;
  std::vector<Comparator> comparators;
  std::string mode;
  std::string name;
};
} // namespace usmt
