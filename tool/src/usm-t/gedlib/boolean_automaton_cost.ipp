#ifndef SRC_EDIT_COSTS_BOOLEAN_AUTOMATON_IPP_
#define SRC_EDIT_COSTS_BOOLEAN_AUTOMATON_IPP_

namespace ged {

template <class UserNodeLabel, class UserEdgeLabel>
BooleanAutomaton<UserNodeLabel, UserEdgeLabel>::~BooleanAutomaton() {}

template <class UserNodeLabel, class UserEdgeLabel>
BooleanAutomaton<UserNodeLabel, UserEdgeLabel>::BooleanAutomaton(
    std::map<std::pair<std::string, std::string>, double>
        &edge_rel_cost_map)
    : edge_rel_cost_map_(edge_rel_cost_map) {}

template <class UserNodeLabel, class UserEdgeLabel>
double
BooleanAutomaton<UserNodeLabel, UserEdgeLabel>::node_ins_cost_fun(
    const UserNodeLabel &node_label) const {
  return node_ins_cost_;
}

template <class UserNodeLabel, class UserEdgeLabel>
double
BooleanAutomaton<UserNodeLabel, UserEdgeLabel>::node_del_cost_fun(
    const UserNodeLabel &node_label) const {
  return node_del_cost_;
}

template <class UserNodeLabel, class UserEdgeLabel>
double
BooleanAutomaton<UserNodeLabel, UserEdgeLabel>::node_rel_cost_fun(
    const UserNodeLabel &node_label_1,
    const UserNodeLabel &node_label_2) const {
  if (node_label_1 != node_label_2) {
    return node_rel_cost_;
  }
  return 0.0;
}

template <class UserNodeLabel, class UserEdgeLabel>
double
BooleanAutomaton<UserNodeLabel, UserEdgeLabel>::edge_ins_cost_fun(
    const UserEdgeLabel &edge_label) const {
  return edge_ins_cost_;
}

template <class UserNodeLabel, class UserEdgeLabel>
double
BooleanAutomaton<UserNodeLabel, UserEdgeLabel>::edge_del_cost_fun(
    const UserEdgeLabel &edge_label) const {
  return edge_del_cost_;
}

template <class UserNodeLabel, class UserEdgeLabel>
double
BooleanAutomaton<UserNodeLabel, UserEdgeLabel>::edge_rel_cost_fun(
    const UserEdgeLabel &edge_label_1,
    const UserEdgeLabel &edge_label_2) const {

  return edge_rel_cost_map_.at(
      std::make_pair(edge_label_1, edge_label_2));
}

} // namespace ged

#endif /* SRC_EDIT_COSTS_BOOLEAN_AUTOMATON_IPP_ */
