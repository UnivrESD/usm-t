#include "gedlibWrapper.hh"
#include "Assertion.hh"
#include "Automaton.hh"
#include "EdgeProposition.hh"
#include "boolean_automaton_cost.hpp"
#include "src/env/ged_env.hpp"

namespace usmt {
using namespace harm;

void computeEditDistance(AssertionPtr a1,
                         const SerializedAutomaton &sa1,
                         AssertionPtr a2,
                         const SerializedAutomaton &sa2,
                         std::map<std::pair<std::string, std::string>,
                                  double> &edge_rel_cost_map) {

  // Instantiate GED environment
  ged::GEDEnv<int, double, std::string> env;
  env.set_edit_costs(new ged::BooleanAutomaton<double, std::string>(
      edge_rel_cost_map));

  ged::GEDGraph::GraphID expected_graph =
      env.add_graph("expected", "ClassA");
  for (auto &[id, label] : sa1.nodes) {
    env.add_node(expected_graph, id, label);
  }
  for (auto &[from, to, label] : sa1.edges) {
    env.add_edge(expected_graph, from, to, label);
  }

  ged::GEDGraph::GraphID mined_graph =
      env.add_graph("mined", "ClassA");

  for (auto &[id, label] : sa2.nodes) {
    env.add_node(mined_graph, id, label);
  }
  for (auto &[from, to, label] : sa2.edges) {
    env.add_edge(mined_graph, from, to, label);
  }

  env.init(ged::Options::InitType::EAGER_WITHOUT_SHUFFLED_COPIES);

  // Set the GED computation method
  env.set_method(ged::Options::GEDMethod::STAR,
                 "--optimal TRUE --threads 1");

  // Initialize the selected method
  env.init_method();

  // Run GED computation between the two graphs
  env.run_method(expected_graph, mined_graph, 0);

  // Retrieve and print the results
  double upper_bound =
      env.get_upper_bound(expected_graph, mined_graph);

  std::cout
      << upper_bound << "/"
      << (std::max(sa1.getNumberEdges() - 2 + sa1.getNumberNodes(),
                   sa2.getNumberEdges() - 2 + sa2.getNumberNodes()))
      << " " << a1->toString() << " vs " << a2->toString() << ": "
      << 1.f - (upper_bound /
                (double)std::max(
                    sa1.getNumberEdges() - 2 + sa1.getNumberNodes(),
                    sa2.getNumberEdges() - 2 + sa2.getNumberNodes()))
      << "\n";
}

SerializedAutomaton serializeAutomaton(Automaton *aut) {
  SerializedAutomaton sa;
  for (const auto &[id, node] : aut->_idToNode) {
    int type = 0;
    if (node->_type == harm::Automaton::Node::Type::Accepting) {
      type = 1;
    } else if (node->_type ==
               harm::Automaton::Node::Type::Rejecting) {
      type = -1;
    } else if (node->_type == harm::Automaton::Node::Type::Pending) {
      type = 0;
    } else {
      messageError("Unknown node type");
    }

    sa.nodes.push_back({(int)id, type});

    for (const auto &edge : node->_outEdges) {
      std::string label = edge->_prop->toString();
      int from = (int)edge->_fromNode->_id;
      int to = (int)edge->_toNode->_id;
      sa.edges.push_back({from, to, label});
    }
  }
  return sa;
}
} // namespace usmt
