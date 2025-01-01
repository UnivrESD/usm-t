#include "EdgeProposition.hh"
#include "expUtils/Z3ExpWrapper.hh"
#include "expUtils/expUtils.hh"
#include "visitors/ExpToZ3Visitor.hh"
#include "z3TestCaseGenerator.hh"
#include <chrono>
#include <exp.hh>
#include <map>
#include <z3++.h>

using namespace expression;

size_t time_spent_by_z3 = 0;

namespace z3 {
PropositionPtr
edgePropositionToProposition(harm::EdgeProposition *edge);

bool check_implies(const expression::PropositionPtr &p1,
                   const expression::PropositionPtr &p2) {
  //make not p1 or p2
  PropositionPtr not_p1_imp_p2 =
      makeGenericExpression<PropositionNot>(
          makeGenericExpression<PropositionImplication>(p1, p2));

  Z3ExpWrapper z3_not_imp = expression::to_z3exp(not_p1_imp_p2);

  //make z3 implication
  z3::context *ctx = z3_not_imp._ctx.get();

  z3::solver s(*ctx);
  z3::params params(*ctx);

  // max 1 second before aborting the solver
  params.set(":timeout", 1000U);
  s.set(params);
  s.add(*z3_not_imp._exp);
  //  std::cout << s << "\n";

  return s.check() == unsat;
}

bool check_equivalence(const expression::PropositionPtr &p1,
                       const expression::PropositionPtr &p2) {

  PropositionPtr not_p1_eq_p2 = makeGenericExpression<PropositionNot>(
      makeGenericExpression<PropositionEq>(p1, p2));

  Z3ExpWrapper z3_not_eq = expression::to_z3exp(not_p1_eq_p2);
  z3::context *ctx = z3_not_eq._ctx.get();

  z3::solver s(*ctx);
  z3::params params(*ctx);

  // max 1 second before aborting the solver
  params.set(":timeout", 1000U);
  s.set(params);

  s.add(*z3_not_eq._exp);

  return s.check() == unsat;
}

bool check_implies(harm::EdgeProposition *edge1,
                   harm::EdgeProposition *edge2) {
  PropositionPtr p1 = edgePropositionToProposition(edge1);
  PropositionPtr p2 = edgePropositionToProposition(edge2);

  auto start = std::chrono::high_resolution_clock::now();
  auto res = check_implies(p1, p2);
  auto end = std::chrono::high_resolution_clock::now();
  time_spent_by_z3 +=
      std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                            start)
          .count();

  return res;

} // end fun

PropositionPtr
edgePropositionToProposition(harm::EdgeProposition *edge) {
  //visit the expression depending on the type of operator

  // And
  if (isEdgeAnd(edge)) {
    std::vector<PropositionPtr> operands;
    auto children = edge->getOperands();
    for (size_t i = 0; i < children.size(); i++) {
      operands.push_back(edgePropositionToProposition(children[i]));
    }
    return makeGenericExpression<PropositionAnd>(operands[0],
                                                 operands[1]);
  }

  // Or
  if (isEdgeOr(edge)) {
    std::vector<PropositionPtr> operands;
    auto children = edge->getOperands();
    for (size_t i = 0; i < children.size(); i++) {
      operands.push_back(edgePropositionToProposition(children[i]));
    }
    return makeGenericExpression<PropositionOr>(operands[0],
                                                operands[1]);
  }

  // Not
  if (isEdgeNot(edge)) {
    return makeGenericExpression<PropositionNot>(
        edgePropositionToProposition(edge->getOperands()[0]));
  }

  // Atomic proposition
  if (isEdgeInst(edge)) {
    return dynamic_cast<harm::EdgeInst *>(edge)->_toInst;
  }

  if (isEdgeTrue(edge)) {
    return generatePtr<BooleanConstant>(true, ExpType::Bool, 1, -1);
  }

  if (isEdgeFalse(edge)) {
    return generatePtr<BooleanConstant>(true, ExpType::Bool, 0, -1);
  }

  messageError("Unknown edge proposition: " + edge->toString());
  return nullptr;
}
} // namespace z3
