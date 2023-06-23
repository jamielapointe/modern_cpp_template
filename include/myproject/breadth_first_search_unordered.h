#pragma once

#include <cstdint>

namespace myproject::algorithms::breadth_first_search_unordered {

template <typename NodeValue>
struct Node {
  using NodeIndex = int64_t;

  NodeIndex node_index;
  NodeValue node_value;

  friend bool operator==(Node const& rhs, Node const& lhs) {
    return rhs.node_index == lhs.node_index;
  }
  friend bool operator!=(Node const& rhs, Node const& lhs) {
    return rhs.node_index != lhs.node_index;
  }
};

template <typename NodeValue, typename DistanceType>
struct Edge {
  Node<NodeValue> node0;
  Node<NodeValue> node1;
};

}  // namespace myproject::algorithms::breadth_first_search_unordered
