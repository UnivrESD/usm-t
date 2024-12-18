#ifndef SRC_EDIT_COSTS_BOOLEAN_AUTOMATON_HPP_
#define SRC_EDIT_COSTS_BOOLEAN_AUTOMATON_HPP_

#include "src/edit_costs/edit_costs.hpp"

namespace ged {

/*!
 * @brief Implements constant edit cost functions.
 */
template <class UserNodeLabel, class UserEdgeLabel>
class BooleanAutomaton
    : public EditCosts<UserNodeLabel, UserEdgeLabel> {

public:
  virtual ~BooleanAutomaton();

  /*!
	 * @brief Constructor.
	 * @param[in] node_ins_cost
	 * @param[in] node_del_cost
	 * @param[in] node_rel_cost
	 * @param[in] edge_ins_cost
	 * @param[in] edge_del_cost
	 * @param[in] edge_rel_cost
	 * @note Calling the constructor with the default arguments constructs uniform edit costs.
	 */
  BooleanAutomaton(std::map<std::pair<std::string, std::string>,
                            double> &edge_rel_cost_map_);

  virtual double
  node_ins_cost_fun(const UserNodeLabel &node_label) const final;

  virtual double
  node_del_cost_fun(const UserNodeLabel &node_label) const final;

  virtual double
  node_rel_cost_fun(const UserNodeLabel &node_label_1,
                    const UserNodeLabel &node_label_2) const final;

  virtual double
  edge_ins_cost_fun(const UserEdgeLabel &edge_label) const final;

  virtual double
  edge_del_cost_fun(const UserEdgeLabel &edge_label) const final;

  virtual double
  edge_rel_cost_fun(const UserEdgeLabel &edge_label_1,
                    const UserEdgeLabel &edge_label_2) const final;

private:
  double node_ins_cost_ = 1.f;
  double node_del_cost_ = 1.f;
  double node_rel_cost_ = 1.f;
  double edge_ins_cost_ = 1.f;
  double edge_del_cost_ = 1.f;
  double edge_rel_cost_ = 1.f;

  std::map<std::pair<std::string, std::string>, double>
      edge_rel_cost_map_;
};

} // namespace ged

#include "boolean_automaton_cost.ipp"

#endif /* SRC_EDIT_COSTS_BOOLEAN_AUTOMATON_HPP_ */
