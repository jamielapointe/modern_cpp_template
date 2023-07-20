///\file undirected_graph.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief Compute the BFS for an unordered graph
///\version 0.1
///\date 2023-06-25
///
///\copyright Copyright (c) 2023
///

#pragma once

#include <cstdint>
#include <functional>
#include <gsl/gsl>
#include <iostream>
#include <memory>
#include <new>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "modern_cpp_template/macros.h"

namespace modern_cpp_template::algorithms::undirected_graph {

///\brief Represent the Node of a graph
///\tparam NodeValue The type of the Value - must support operator<<
template <typename NodeValue>
struct Node {
  using NodeIndex = gsl::index;

  ///\brief true if this node has been visited by a search algorithm; otherwise
  /// false
  bool is_visited{false};

  ///\brief The key id of the Node
  NodeIndex id{0};

  ///\brief The value of the Node
  NodeValue value{};

  ///\brief return the nodes Key which can be hashed
  ///\return NodeIndex
  [[gnu::nothrow]] NodeIndex key() const { return id; }

  ///\brief output stream operator - puts a string representation of the node
  /// onto the std::ostream
  ///\param os an existing std::ostream
  ///\param node a node to "print" to the std::ostream
  ///\return std::ostream& a reference to the std::ostream
  friend std::ostream& operator<<(std::ostream& os, Node const& node) {
    os << "Node ID: " << node.id << " = " << node.value;
    return os;
  }

  ///\brief equality operator for two Node types
  ///
  ///\param rhs Node
  ///\param lhs Node
  ///\return true if the nodes are equal
  ///\return false if the nodes are not equal
  friend bool operator==(Node const& rhs, Node const& lhs) {
    return rhs.id == lhs.id;
  }

  ///\brief inequality operator for two Node types
  ///
  ///\param rhs Node
  ///\param lhs Node
  ///\return true if the nodes are not equal
  ///\return false if the nodes are equal
  friend bool operator!=(Node const& rhs, Node const& lhs) {
    return rhs.id != lhs.id;
  }
};

///\brief Representation of an edge of a graph
/// An Edge connects exactly two Node types of a graph.  The Edge object stores
/// a pointer to the node rather than the node itself so that we can easily
/// reference the original object when we need to set the is_visited flag on it.
///\tparam NodeValue_T The value type of a Node
///\tparam CostType_t The cost type for the edge cost - expected to be some kind
/// of numeric type
template <typename NodeValue_T, typename CostType_T>
struct Edge {
  using NodeValue = NodeValue_T;
  using CostType = CostType_T;
  using Node_T = Node<NodeValue>;
  using NodeIndex = typename Node_T::NodeIndex;

  ///\brief The head Node index of the edge on one side of the edge
  NodeIndex head_node_index{0};

  ///\brief The pointer to the tail Node on the other side of the edge
  NodeIndex tail_node_index{0};

  ///\brief The cost of this edge
  CostType cost{0};
};

///\brief An undirected graph
/// In an undirected graph an edge does not have direction.  To compensate for
/// this, when we add an edge we add its mirror copy.  For example, if adding
/// and edge between two nodes A and B, then we have edge 1 from from A to B and
/// then its opposite copy, edge 2 going from B to A.
///\tparam NodeValue_T The value stored in a Node
///\tparam CostType_T The type of the cost of an Edge
template <typename NodeValue_T, typename CostType_T>
class UndirectedGraph {
 public:
  using NodeValue = NodeValue_T;
  using CostType = CostType_T;
  using Edge_T = Edge<NodeValue, CostType>;
  using Node = typename Edge_T::Node_T;
  using NodeIndex = typename Edge_T::NodeIndex;
  using EdgeList = std::vector<Edge_T>;
  using NodeAdjacencyMap = std::unordered_map<NodeIndex, EdgeList>;
  using NodeMap = std::unordered_map<NodeIndex, Node>;

  ///\brief Construct a new Undirected Graph object
  /// Sets the initial size for the number of nodes and number of edges.  For
  /// large graphs, setting the number of nodes and the number of edges first
  /// makes creating the graph much more efficient.
  ///\param num_nodes the initial number of nodes
  ///\param num_edges the initial number of edges
  explicit UndirectedGraph(std::size_t num_nodes, std::size_t num_edges)
      : node_map_(num_nodes), adjacency_map_(num_edges) {}

  ///\brief Construct a new Undirected Graph object
  UndirectedGraph() = default;

  ///\brief return the number of nodes in the graph
  ///\return auto the number of nodes in the graph
  auto number_of_nodes() { return node_map_.size(); }

  ///\brief return the number of edges in the graph
  ///\return auto the number of edges in the graph
  auto number_of_edges() { return adjacency_map_.size(); }

  ///\brief Readonly accessor for the adjacency map
  /// The adjacency map maps the key of a Node (NodeIndex) to its
  /// list of directly connected edges.  this is equivalent to an
  /// Adjacency List
  ///\return NodeAdjacencyMap const&
  [[gnu::nothrow]] NodeAdjacencyMap const& adjacency_map() const {
    return adjacency_map_;
  }

  ///\brief Accessor for the adjacency map
  /// The adjacency map maps the key of a Node (NodeIndex) to its
  /// list of directly connected edges.  this is equivalent to an
  /// Adjacency List
  ///\return NodeAdjacencyMap const&
  [[gnu::nothrow]] NodeAdjacencyMap& adjacency_map() { return adjacency_map_; }

  ///\brief Readonly accessor for the Node map
  /// The node_map maps the key ofa Node (NodeIndex) to the Node it represents
  ///\return NodeMap const&
  [[gnu::nothrow]] NodeMap const& node_map() const { return node_map_; }

  ///\brief Accessor for the Node map
  /// The node_map maps the key ofa Node (NodeIndex) to the Node it represents
  ///\return NodeMap const&
  [[gnu::nothrow]] NodeMap& node_map() { return node_map_; }

  // ///\brief Return the readonly list of Edge objects for a specific node
  // /// This will return the list of Edge objects that are directly connected
  // to
  // /// the Node represented by the NodeIndex
  // ///\param node_index The key of the Node whose Edge objects you want to
  // return
  // ///\return EdgeList&
  // EdgeList const& get_edges(NodeIndex node_index) const {
  //   modern_cpp_template_assert(node_index >= 0 &&
  //                              node_index < adjacency_map().size());
  //   typename NodeAdjacencyMap::const_iterator edge_iterator =
  //       adjacency_map().find(node_index);
  //   [[likely]] if (edge_iterator != adjacency_map().end()) {
  //     return edge_iterator->second;
  //   }
  //   return kEmptyEdgeList;
  // }

  ///\brief Return the list of Edge objects for a specific node
  /// This will return the list of Edge objects that are directly connected to
  /// the Node represented by the NodeIndex
  ///\param node_index The key of the Node whose Edge objects you want to return
  ///\return EdgeList&
  EdgeList& get_edges(NodeIndex node_index) {
    modern_cpp_template_assert(node_index >= 0 &&
                               static_cast<size_t>(node_index) <
                                   adjacency_map().size());
    typename NodeAdjacencyMap::iterator edge_iterator =
        adjacency_map().find(node_index);
    [[likely]] if (edge_iterator != adjacency_map().end()) {
      return edge_iterator->second;
    }
    return kEmptyEdgeList;
  }

  // ///\brief Return the readonly Node from the node index
  // ///\param node_index The node index
  // ///\return Node const&
  // Node const& get_node(NodeIndex node_index) const {
  //   modern_cpp_template_assert(
  //       node_index >= 0 && static_cast<size_t>(node_index) <
  //       node_map().size());
  //   typename NodeMap ::const_iterator node_iterator =
  //   node_map().find(node_index);
  //   [[likely]] if (node_iterator != node_map().end()) {
  //     return node_iterator->second;
  //   }
  //   return kEmptyNode;
  // }

  ///\brief Return the Node from the node index
  ///\param node_index The node index
  ///\return Node const&
  Node& get_node(NodeIndex node_index) {
    modern_cpp_template_assert(
        node_index >= 0 && static_cast<size_t>(node_index) < node_map().size());
    auto node_iterator = node_map().find(node_index);
    [[likely]] if (node_iterator != node_map().end()) {
      return node_iterator->second;
    }
    return kEmptyNode;
  }

  ///\brief Add an Edge to the Graph
  /// Because this is an undirected graph, this will add two edges swapping the
  /// Node for the head_node and tail_node
  ///\param head_node A Node on one of the ends of an Edge
  ///\param tail_node A Node on one of the ends of an Edge
  ///\param edge_cost The optional cost of the Edge - default is 0 or no cost
  ///@note This induces two copies.  Which is fine for small
  // Nodes.  We should employ a mechanism to either move or construct in
  // place... similar to emplace_back for a std::vector.
  void add_edge(Node head_node, Node tail_node,
                CostType edge_cost = static_cast<CostType>(0)) {
    node_map()[head_node.id] = head_node;
    node_map()[tail_node.id] = tail_node;
    adjacency_map()[head_node.id].emplace_back(
        Edge_T{head_node.id, tail_node.id, edge_cost});
    adjacency_map()[tail_node.id].emplace_back(
        Edge_T{tail_node.id, head_node.id, edge_cost});
  }

  ///\brief Add an edge to the Graph
  /// Because this is an undirected graph, this will add two edges swapping the
  /// Node for the head_node and tail_node.  Head and Tail have no real meaning
  /// for an undirected graph and just mean two ends of an Edge.
  ///\param head_node_index Index of the head Node
  ///\param head_node_value Value of the head Node
  ///\param tail_node_index Index of the tail Node
  ///\param tail_node_value Value of the tail Node
  ///\param edge_cost Cost of the edge
  void add_edge(NodeIndex head_node_index, NodeValue head_node_value,
                NodeIndex tail_node_index, NodeValue tail_node_value,
                CostType edge_cost = 0) {
    node_map().emplace(head_node_index,
                       Node{false, head_node_index, head_node_value});
    node_map().emplace(tail_node_index,
                       Node{false, tail_node_index, tail_node_value});
    adjacency_map()[head_node_index].emplace_back(
        Edge_T{head_node_index, tail_node_index, edge_cost});
    adjacency_map()[tail_node_index].emplace_back(
        Edge_T{tail_node_index, head_node_index, edge_cost});
  }

  ///\brief Perform the BFS (breadth first search) algorithm on the graph
  /// In general, this algorithm will terminate when all reachable nodes from
  /// the start_node have been exhausted.  However, a user may pass an optional
  /// callback function that returns a bool.  If this optional callback return
  /// true, then this algorithm will terminate early.  This is useful if you
  /// are searching for a specific Node.  You would naturally want to
  /// terminate the search when the Node has been located.
  ///\param start_node_index the Node to start the algorithm at
  ///\param callback the optional function to call to process each new node
  /// found in the search.  This function will return a bool type.  If the
  /// function returns true, then this algorithm is terminated early.
  void breadth_first_search(
      NodeIndex start_node_index,
      std::function<bool(Node const&)> callback = nullptr) {
    // "Visit" the start_node and add it to the queue and call the callback if
    // it exists
    auto& start_node = get_node(start_node_index);
    std::queue<NodeIndex> node_queue;
    start_node.is_visited = true;
    if (callback != nullptr) {
      callback(start_node);
    }
    node_queue.push(start_node.id);
    // process reachable nodes added to the node queue.  We are finished when
    // the node queue is empty
    while (!node_queue.empty()) {
      auto node_index = node_queue.front();
      auto& node_edges = get_edges(node_index);
      node_queue.pop();
      // process unvisited nodes directly reachable (i.e., an edge exists from
      // the current "head node" to the "tail node") from "node".  Process means
      // to call the callback function and add the tail node to the node_queue
      for (auto& node_edge : node_edges) {
        auto& tail_node = get_node(node_edge.tail_node_index);
        if (!tail_node.is_visited) {
          tail_node.is_visited = true;
          if (callback != nullptr) {
            if (callback(tail_node)) {
              return;
            }
          }
          node_queue.push(tail_node.id);
        }
      }
    }
  }

 private:
  NodeMap node_map_{};
  NodeAdjacencyMap adjacency_map_{};
  Node kEmptyNode{};
  EdgeList kEmptyEdgeList{};
};

}  // namespace modern_cpp_template::algorithms::undirected_graph
