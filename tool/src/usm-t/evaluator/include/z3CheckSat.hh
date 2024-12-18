#pragma once
#pragma once
#include "expUtils/Z3ExpWrapper.hh"
#include "formula/atom/Atom.hh"

#include "message.hh"
namespace z3 {

bool check_implies(const expression::PropositionPtr &p1,
                   const expression::PropositionPtr &p2);

}
