#include "expUtils/Z3ExpWrapper.hh"
#include "expUtils/expUtils.hh"
#include "visitors/ExpToZ3Visitor.hh"
#include "z3TestCaseGenerator.hh"
#include <exp.hh>
#include <z3++.h>

using namespace expression;

namespace z3 {

bool check_implies(const expression::PropositionPtr &p1,
                   const expression::PropositionPtr &p2) {
  //make not p1 or p2

  PropositionPtr not_p1_or_not_p2 =
      makeGenericExpression<PropositionNot>(
          makeGenericExpression<PropositionOr>(
              makeGenericExpression<PropositionNot>(p1), p2));

  Z3ExpWrapper not_p1_or_not_p2_z3w =
      expression::to_z3exp(not_p1_or_not_p2);

  //make z3 implication
  z3::context *ctx = not_p1_or_not_p2_z3w._ctx.get();

  z3::solver s(*ctx);
  z3::params params(*ctx);

  // max 1 second before aborting the solver
  params.set(":timeout", 1000U);
  s.set(params);
  s.add(*not_p1_or_not_p2_z3w._exp);

  return s.check() == unsat;

} // end fun

} // namespace z3
