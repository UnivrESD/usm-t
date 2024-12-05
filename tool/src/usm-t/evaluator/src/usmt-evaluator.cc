#include "PathHandler.hh"
#include "message.hh"
#include "misc.hh"
#include <filesystem>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

//spot includes
#include "AutomataBasedEvaluator.hh"
#include "spot/twa/bddprint.hh"
#include "spot/twa/twa.hh"
#include "spot/twa/twagraph.hh"
#include "spot/twaalgos/translate.hh"
#include <spot/tl/formula.hh>
#include <spot/tl/ltlf.hh>
#include <spot/tl/parse.hh>
#include <spot/tl/print.hh>
#include <spot/twaalgos/contains.hh>
#include <spot/twaalgos/hoa.hh>
#include <spot/twaalgos/isdet.hh>
#include <spot/twaalgos/postproc.hh>
#include <spot/twaalgos/remprop.hh>

#include "Assertion.hh"
#include "usmt-evaluator.hh"

//normal include
namespace usmt {
using namespace harm;

int compareLanguage(harm::AssertionPtr a1, harm::AssertionPtr a2) {
  //ret 0 if equivalent, 1 if a1 contains a2, 2 if a2 contains a1, -1 if not

  std::string a1_str = a1->toString(Language::SpotLTL);
  std::string a2_str = a2->toString(Language::SpotLTL);

  spot::formula p1 = spot::parse_formula(a1_str);
  spot::formula p2 = spot::parse_formula(a2_str);

  if (spot::are_equivalent(p1, p2)) {
    return 0;
  } else {
    if (spot::contains(p1, p2) == 1) {
      return 1;
    } else if (spot::contains(p2, p1) == 1) {
      return 2;
    }
  }
  return -1;
}

int testEmpty(harm::AssertionPtr a1, harm::AssertionPtr a2) {
  //ret 0 if equivalent, 1 if a1 contains a2, 2 if a2 contains a1, -1 if not

  std::string a1_str = a1->toString(Language::SpotLTL);
  std::string a2_str = a2->toString(Language::SpotLTL);

  std::string test_formula = a1_str + " && !(" + a2_str + " )";
  spot::formula f = spot::parse_formula(test_formula);
  auto aut = generateDeterministicSpotAutomaton(f);

  int res = -1;

  if (aut->num_states() == 1) {
    res = 2;
  }

  test_formula = "!(" + a1_str + ") && " + a2_str;
  f = spot::parse_formula(test_formula);
  aut = generateDeterministicSpotAutomaton(f);

  if (aut->num_states() == 1) {
    if (res == 2) {
      res = 0;
    } else {
      res = 1;
    }
  }

  return res;
}

void evaluateExpectedvsMined(const usmt::PathHandler &ph,
                             const usmt::UseCase &use_case) {}
} // namespace usmt
