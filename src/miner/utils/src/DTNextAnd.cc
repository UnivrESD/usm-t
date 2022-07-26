#include "DTNextAnd.hh"
#include "DTUtils.hh"
#include "Template.hh"
#include "message.hh"
#include "minerUtils.hh"
#include <spot/tl/formula.hh>
#include <spot/twaalgos/postproc.hh>
#include <string>
#include <unordered_set>
#include <utility>

namespace harm {
//--DTNextAnd---------------------------------------

DTNextAnd::DTNextAnd(size_t shift, Template *t, const DTLimits &limits)
    : _t(t), _shift(shift) {

  _limits = limits;
  _tc = new BooleanConstant(true, VarType::Bool, 1, t->_max_length);
  // The base case automata were already generated in the template
  _tokens.push_back("dtNextAnd0");
  _leaves.emplace_back();
  _op.push_back(
      dynamic_cast<PropositionAnd *>(*_t->_tokenToProp.at("dtNextAnd0")));
  _ant.push_back(_t->_ant);
  // storing depths
  _antDepth.push_back(_t->getDepth(_ant.back()));

  // adjust offset:  we shouldn't have any delaying when we have only one
  // operand
  for (size_t j = 0; j < t->_templateFormula.size(); j++) {
    if (t->_templateFormula[j]._t == Hstring::Stype::DTNextAnd) {
      t->_templateFormula[j]._offset = 0;
    }
  }
  _formulas.push_back(t->_templateFormula);

  if (_t->_applyDynamicShift) {
    _applyDynamicShift = true;
    messageErrorIf(
        !nothingBefore(
            _tokens.back(),
            spot::parse_infix_psl(_t->_templateFormula.getAnt().toSpotString())
                .f),
        "Can't have events happening before the dtNext operator when using "
        "|-> ");
  } else {
    messageErrorIf(
        !nothingAfter(
            _tokens.back(),
            spot::parse_infix_psl(_t->_templateFormula.getAnt().toSpotString())
                .f),
        "Can't have events happening after the dtNext operator when not using "
        "|-> ");
  }

  //  messageInfo("Building automata...");

  // retrieve the consequent and the implication of the formula
  std::string imp = t->_templateFormula.getImp()._s;
  // remove unwanted spaces in the string representation of the implication
  imp.erase(remove_if(imp.begin(), imp.end(), isspace), imp.end());
  auto hcon = t->_templateFormula.getCon();

  // generate the rest of the automata
  for (size_t i = 1; i < _limits._maxDepth; i++) {
    // we build on the previous automa
    auto hant = _formulas[i - 1].getAnt();

    if (_t->_applyDynamicShift) {
      // dtNextM ##N dtNextM-1 ##N ... ##N dtNext0
      // last insertion point
      size_t lastIP = -1;
      // find the last operand and append a new one
      for (size_t j = 0; j < hant.size(); j++) {
        if (hant[j]._t == Hstring::Stype::DTNextAnd) {
          Proposition **pp =
              new Proposition *(makeExpression<PropositionAnd>());
          std::string token = "dtNextAnd" + std::to_string(i);
          hant.insert(hant.begin() + j,
                      Hstring(token, Hstring::Stype::DTNextAnd, pp));
          hant[j]._offset = _shift;
          // the relation between token name and proposition is kept in the
          // template
          _t->_tokenToProp[token] = pp;
          _tokens.push_back(token);
          _leaves.emplace_back();
          _op.push_back(dynamic_cast<PropositionAnd *>(*pp));
          lastIP = j;
          break;
        }
      }
      // adjust offset: only the last operand should have delay equal to 0
      hant[lastIP]._offset = 0;
      for (size_t j = lastIP + 1; j < hant.size(); j++) {
        if (hant[j]._t == Hstring::Stype::DTNextAnd) {
          hant[j]._offset = _shift;
        }
      }
    } else {

      // dtNext1 ##N dtNext2 ##N ... ##N dtNextM
      // find the last operand and append a new one
      for (int j = hant.size() - 1; j >= 0; j--) {
        if (hant[j]._t == Hstring::Stype::DTNextAnd) {
          Proposition **pp =
              new Proposition *(makeExpression<PropositionAnd>());
          std::string token = "dtNextAnd" + std::to_string(i);
          hant.insert(hant.begin() + j + 1,
                      Hstring(token, Hstring::Stype::DTNextAnd, pp));
          hant[j]._offset = _shift;
          // the relation between token name and proposition is kept in the
          // template
          _t->_tokenToProp[token] = pp;
          _op.push_back(dynamic_cast<PropositionAnd *>(*pp));
          _tokens.push_back(token);
          _leaves.emplace_back();
          break;
        }
      }
      // adjust offset: only the first operand should have delay equal to 0
      size_t firstDT = 0;
      for (size_t j = 0; j < hant.size(); j++) {
        if (hant[j]._t == Hstring::Stype::DTNextAnd) {
          firstDT = j;
          break;
        }
      }
      hant[firstDT]._offset = 0;
      for (size_t j = firstDT + 1; j < hant.size(); j++) {
        if (hant[j]._t == Hstring::Stype::DTNextAnd) {
          hant[j]._offset = _shift;
        }
      }
    }

    _formulas.push_back(Hstring("G(", Hstring::Stype::G) + hant +
                        Hstring(" " + imp + " ", Hstring::Stype::Imp, nullptr) +
                        hcon + Hstring(")", Hstring::Stype::G));

    // string to spot formula
    spot::parsed_formula ant = spot::parse_infix_psl(hant.toSpotString());

    auto antAutomaton = t->generateDeterministicSpotAutomaton(ant.f);

    // building storing our custom automata
    _ant.push_back(_t->buildAutomaton(antAutomaton));

    // storing depths
    _antDepth.push_back(_t->getDepth(_ant.back()));

    //    std::cout << _formulas.back().toSpotString() << "\n";
  }
  // stop progress bar
  //  for (auto i : _tokens) {
  //    std::cout << i << "\n";
  //  }
  //  for (auto &e : _formulas) {
  //    std::cout << e.toSpotString() << "\n";
  //  }

  //   Check for parallel depth
  if (_t->_applyDynamicShift) {
    int baseDepth = -1;
    for (auto f : _formulas) {
      auto portionBare =
          selectFirstEvent(spot::parse_infix_psl(f.getAnt().toSpotString()).f);
      std::stringstream ss;
      print_spin_ltl(ss, portionBare, false) << '\n';
      std::string portion = "{" + ss.str() + "}";
      auto portionFormula = spot::parse_infix_psl(portion);
      // print_spin_ltl(std::cout, portionFormula.f, false) << '\n';
      auto antAutomaton =
          t->generateDeterministicSpotAutomaton(portionFormula.f);
      Automaton *pAnt = _t->buildAutomaton(antAutomaton);
      int depth = _t->getDepth(pAnt);

      messageErrorIf(depth == -1, " parallel depth is unknown");
      baseDepth = (baseDepth == -1 ? depth : baseDepth);
      if (depth == 0) {
        if (!onlyToken("dtNextAnd0", portionFormula.f)) {
          _parallelDepth++;
        }
        delete pAnt;
        break;
      } else if (baseDepth == depth) {
        _parallelDepth++;
      }
      delete pAnt;
    }
  }
  //  std::cout << "PD:" << _parallelDepth << "\n";
  if (_parallelDepth != 0) {
    _limits._maxDepth =
        _parallelDepth < _limits._maxDepth ? _parallelDepth : _limits._maxDepth;
    //    messageWarning(" Max dt operands reduced to " +
    //    std::to_string(_parallelDepth) + " due to parallel depth");
    _t->_ant = _ant[_limits._maxDepth - 1];
    _t->_templateFormula = _formulas[_limits._maxDepth - 1];
    _t->_antDepth = _antDepth[_limits._maxDepth - 1];

    removeItems();
  }
}

DTNextAnd::~DTNextAnd() {
  for (size_t i = 0; i < _tokens.size(); i++) {
    delete _ant[i];
  }
  for (size_t i = 0; i < _tokens.size(); i++) {
    _op[i]->removeItems();
    delete _op[i];
  }
  delete _tc;
}
std::vector<Proposition *> DTNextAnd::minimize(bool isOffset) {
  std::vector<std::pair<Proposition *, size_t>> propList;

  for (size_t i = 0; i <= _currDepth; i++) {
    for (auto &p : _op[i]->getItems()) {
      propList.emplace_back(p, i);
    }
  }

  // keep track of the original choices
  std::vector<std::pair<Proposition *, size_t>> originalChoices;
  std::unordered_map<size_t, size_t> orderToShift;
  for (auto o : _order) {
    originalChoices.emplace_back(_choices.at(o)[orderToShift[o]++], o);
  }

  std::vector<std::vector<size_t>> c;
  for (size_t i = 1; i <= propList.size(); i++) {
    // clear the current combinations
    c.clear();
    // generate combinations for size i
    comb(propList.size(), i, c);
    // find a combination that satisfies the assertion
    for (auto &comb : c) {
      // fill with all true constants
      for (size_t j = 0; j <= _currDepth; j++) {
        _op[j]->removeItems();
      }

      // load the combination
      for (auto &e : comb) {
        _op[propList[e].second]->addItem(propList[e].first);
      }
      // check if this combination works
      if (isOffset) {
        if (_t->assHoldsOnTraceOffset(harm::Location::Ant)) {
          // we found a minimal solution
          goto end;
        }
      } else {
        if (_t->assHoldsOnTrace(harm::Location::Ant)) {
          goto end;
        }
      }
    }
  }
end:;

  std::vector<Proposition *> ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    PropositionAnd *andP = _op[i];
    std::vector<Proposition *> tmp;
    for (auto &e : andP->getItems()) {
      tmp.push_back(e);
    }
    sortPropositions(tmp);
    PropositionAnd *tmp1 = makeExpression<PropositionAnd>();
    for (auto &e : tmp) {
      tmp1->addItem(e);
    }
    ret.push_back(tmp1);
  }

  // restore
  removeItems();
  for (auto p_d : originalChoices) {
    addItem(p_d.first, p_d.second);
  }

  return ret;
}
void DTNextAnd::removeItems() {

  if (_parallelDepth) {
    for (size_t i = 0; i <= _currDepth; i++) {
      _op[i]->removeItems();
    }
  } else {
    for (size_t i = 0; i <= _currDepth; i++) {
      _op[i]->removeItems();
    }
    _t->_ant = _ant[0];
    _t->_templateFormula = _formulas[0];
    _t->_antDepth = _antDepth[0];
  }
  _choices.clear();
  _order.clear();
  _currDepth = 0;
}
void DTNextAnd::popItem(int depth) {
  assert(depth != -1);
  if (_parallelDepth) {
    _op[depth]->popItem();
  } else {
    _op[depth]->popItem();
    if ((size_t)depth == _currDepth) {
      while (_currDepth > 0 && _op[_currDepth]->empty()) {
        _currDepth--;
      }
    }
    _t->_ant = _ant[_currDepth];
    _t->_templateFormula = _formulas[_currDepth];
    _t->_antDepth = _antDepth[_currDepth];
  }

  assert(!_choices.at(depth).empty());
  _choices.at(depth).pop_back();
  _order.pop_back();
  assert(std::accumulate(_choices.begin(), _choices.end(), 0ul,
                         [](size_t &a, auto &e) { return a + e.second.size(); }) ==
         _order.size());
}
void DTNextAnd::addItem(Proposition *p, int depth) {

  assert(depth != -1);
  _order.push_back(depth);
  if (_parallelDepth) {
    _op[depth]->addItem(p);
    _choices[depth].push_back(p);
  } else {
    _op[depth]->addItem(p);
    _choices[depth].push_back(p);
    if ((size_t)depth > _currDepth) {
      _currDepth = depth;
      _t->_ant = _ant[_currDepth];
      _t->_templateFormula = _formulas[_currDepth];
      _t->_antDepth = _antDepth[_currDepth];
    }
  }
  assert(std::accumulate(_choices.begin(), _choices.end(), 0ul,
                         [](size_t &a, auto &e) { return a + e.second.size(); }) ==
         _order.size());
}
std::vector<Proposition *> DTNextAnd::getItems() {
  std::vector<Proposition *> ret;
  for (size_t i = 0; i <= _currDepth; i++) {
    ret.push_back(_op[i]);
  }
  return ret;
}
bool DTNextAnd::isMultiDimensional() { return 1; }
bool DTNextAnd::canInsertAtDepth(int depth) {
  assert(depth != -1);
  return (_choices[depth].size() < _limits._maxWidth &&
          (size_t)depth < _limits._maxDepth);
}
bool DTNextAnd::isRandomConstructed() { return _limits._isRandomConstructed; }
size_t DTNextAnd::getNChoices() { return _order.size(); }
bool DTNextAnd::isTaken(size_t id, bool second, int depth) {
  assert(depth != -1);
  if (second) {
    return _leaves[depth].count(id) && _leaves[depth].at(id).second != nullptr;
  } else {
    return _leaves[depth].count(id) && _leaves[depth].at(id).first != nullptr;
  }
}
void DTNextAnd::removeLeaf(size_t id, bool second, int depth) {
  assert(depth != -1);
  if (second) {
    _leaves[depth].at(id).second = nullptr;
  } else {
    _leaves[depth].at(id).first = nullptr;
  }
}
void DTNextAnd::addLeaf(Proposition *p, size_t id, bool second, int depth) {
  assert(depth != -1);
  if (second) {
    _leaves[depth][id].second = p;
  } else {
    _leaves[depth][id].first = p;
  }
}
const DTLimits &DTNextAnd::getLimits() { return _limits; }
size_t DTNextAnd::getCurrentDepth() { return _currDepth; }

void DTNextAnd::clearPack(Proposition *pack) {
  dynamic_cast<PropositionAnd *>(pack)->removeItems();
}
std::vector<Proposition *> DTNextAnd::unpack() {
  std::vector<Proposition *> ret;
  for (auto &pack : getItems()) {
    std::vector<Proposition *> sorted = unpack(pack);
    ret.insert(end(ret), begin(sorted), end(sorted));
  }
  return ret;
}
std::vector<Proposition *> DTNextAnd::unpack(Proposition *pack) {
  std::vector<Proposition *> ret;
  if (dynamic_cast<PropositionAnd *>(pack)->empty()) {
    ret.push_back(_tc);
  } else {
    for (auto &item : dynamic_cast<PropositionAnd *>(pack)->getItems()) {
      ret.push_back(item);
    }
  }
  sortPropositions(ret);

  return ret;
}
std::vector<Proposition *>
DTNextAnd::unpack(std::vector<Proposition *> &pack) {
  std::vector<Proposition *> ret;
  for (auto &p : pack) {
    std::vector<Proposition *> sorted = unpack(p);
    ret.insert(end(ret), begin(sorted), end(sorted));
  }
  return ret;
}

std::pair<std::string, std::string> DTNextAnd::prettyPrint(bool offset) {

  std::vector<std::vector<Proposition *>> original;
  for (size_t i = 0; i <= _currDepth; i++) {
    original.emplace_back();
    for (auto p : _op[i]->getItems()) {
      original.back().push_back(p);
    }
  }

  auto solTemplate = _formulas[_currDepth];

  size_t dtIndex = _t->_applyDynamicShift ? 0 : _currDepth;
  size_t comulativeShift = 0;
  size_t lastCandidate = 0;
  std::unordered_set<size_t> toDelete;
  std::map<size_t, std::pair<PropositionAnd *, size_t>> toUpdate;

  // slide bw
  for (int j = solTemplate.size() - 1; j >= 0; j--) {
    if (solTemplate[j]._t == Hstring::Stype::DTNextAnd) {
      PropositionAnd *p = dynamic_cast<PropositionAnd *>(_op[dtIndex]);
      // base case
      if (_t->_applyDynamicShift ? (dtIndex == 0) : (dtIndex == _currDepth)) {
        toUpdate.insert(
            {{dtIndex, std::pair(p, _currDepth == 0 ? 0 : _shift)}});
        lastCandidate = dtIndex;
        dtIndex = _t->_applyDynamicShift ? dtIndex + 1 : dtIndex - 1;
        continue;
      }
      assert(!p->empty());
      if (p->getItems().size() == 1 && (dtIndex <= _currDepth) &&
          dynamic_cast<BooleanConstant *>(p->getItems().back()) != nullptr) {
        comulativeShift += _shift;
        toDelete.insert(dtIndex);
        //        std::cout << "toD:" << prop2String(*p) << "\n";
      } else {
        toUpdate.at(lastCandidate).second += comulativeShift;
        //        std::cout << "toU:" <<
        //        prop2String(*toUpdate.at(lastCandidate).first)
        //                  << "," << toUpdate.at(lastCandidate).second << "\n";
        lastCandidate = dtIndex;
        toUpdate.insert({{dtIndex, std::pair(p, solTemplate[j]._offset)}});
        comulativeShift = 0;
      }
      dtIndex = _t->_applyDynamicShift ? dtIndex + 1 : dtIndex - 1;
    }
  }
  if (toDelete.count(_t->_applyDynamicShift ? dtIndex - 1 : dtIndex + 1)) {
    toUpdate.at(lastCandidate).second += (comulativeShift - _shift);
  }

  //  std::cout << "-------toU:" <<
  //  prop2String(*toUpdate.at(lastCandidate).first)
  //            << "," << toUpdate.at(lastCandidate).second << "\n";

  auto reducedTemplate = _formulas[_currDepth - toDelete.size()];
  for (int j = reducedTemplate.size() - 1; j >= 0; j--) {
    if (reducedTemplate[j]._t == Hstring::Stype::DTNextAnd) {
      size_t adjustedIndex = _t->_applyDynamicShift ? toUpdate.begin()->first
                                                    : toUpdate.rbegin()->first;
      reducedTemplate[j]._offset = toUpdate.at(adjustedIndex).second;
      PropositionAnd *toChange =
          dynamic_cast<PropositionAnd *>((*reducedTemplate[j]._pp));
      toChange->removeItems();
      for (size_t i = 0; i < original[adjustedIndex].size(); i++) {
        toChange->addItem(original[adjustedIndex][i]);
      }

      toUpdate.erase(adjustedIndex);
    }
  }

  if (offset) {
    for (int j = reducedTemplate.size() - 1; j >= 0; j--) {
      if (reducedTemplate[j]._t == Hstring::Stype::Imp) {
        reducedTemplate.insert(reducedTemplate.begin() + j + 1,
                               Hstring("!(", Hstring::Stype::Temp, nullptr));
        reducedTemplate.insert(reducedTemplate.end() - 1,
                               Hstring(")", Hstring::Stype::Temp, nullptr));
        break;
      }
    }
  }
  auto ret = std::make_pair(reducedTemplate.toString(1),
                            reducedTemplate.toColoredString(1));

  for (size_t i = 0; i < original.size(); i++) {
    _op[i]->removeItems();
    for (auto p : original[i]) {
      _op[i]->addItem(p);
    }
  }
  return ret;
}
void DTNextAnd::substitute(int depth, int width, Proposition *&sub) {
  if (depth == -1) {
    depth = _currDepth;
  }
  if (width == -1) {
    width = _choices.at(depth).size() - 1;
  }
  Proposition *tmp = _choices.at(depth)[width];
  _choices.at(depth)[width] = sub;
  _op[depth]->getItems()[width] = sub;
  sub = tmp;
}

} // namespace harm
