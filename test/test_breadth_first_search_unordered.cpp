#include <gtest/gtest.h>

#include <vector>

#include "modern_cpp_template/undirected_graph.h"

namespace {

using Graph =
    modern_cpp_template::algorithms::undirected_graph::UndirectedGraph<
        std::string, int64_t>;
using Node = Graph::Node;
using NodeIndex = Graph::NodeIndex;

// clang-format off
TEST(BreadthFirstSearchUndirectedTest, Test0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  // clang-format on

  static constexpr NodeIndex nodeid0{0};
  static constexpr NodeIndex nodeid1{1};
  static constexpr NodeIndex nodeid2{2};
  static constexpr NodeIndex nodeid3{3};
  static constexpr NodeIndex nodeid4{4};
  static constexpr NodeIndex nodeid5{5};
  static constexpr NodeIndex nodeid6{6};
  static constexpr NodeIndex nodeid7{7};
  static constexpr NodeIndex nodeid8{8};
  static constexpr NodeIndex nodeid9{9};

  static constexpr size_t kNumNodes{10};
  static constexpr size_t kNumEdges{10};

  Node node0{false, nodeid0, "Frankfurt"};
  Node node1{false, nodeid1, "Mannheim"};
  Node node2{false, nodeid2, "Würzburg"};
  Node node3{false, nodeid3, "Kassel"};
  Node node4{false, nodeid4, "Karlsruhe"};
  Node node5{false, nodeid5, "Nürnberg"};
  Node node6{false, nodeid6, "Erfurt"};
  Node node7{false, nodeid7, "München"};
  Node node8{false, nodeid8, "Augsburg"};
  Node node9{false, nodeid9, "Stuttgart"};

  std::vector<Node> bfs_expected_node_container{
      node0, node1, node2, node3, node4, node5, node6, node7, node8, node9};
  std::vector<Node> bfs_node_container;

  Graph graph(kNumNodes, kNumEdges);
  graph.add_edge(node0, node1);
  graph.add_edge(node0, node2);
  graph.add_edge(node0, node3);
  graph.add_edge(node1, node4);
  graph.add_edge(node2, node5);
  graph.add_edge(node2, node6);
  graph.add_edge(node3, node7);
  graph.add_edge(node4, node8);
  graph.add_edge(node5, node9);

  graph.breadth_first_search(nodeid0, [&bfs_node_container](Node const& node) {
    bfs_node_container.push_back(node);
    return false;
  });
  ASSERT_EQ(bfs_node_container, bfs_expected_node_container);
}

// clang-format off
TEST(BreadthFirstSearchUndirectedTest, Test1) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  // clang-format on

  static constexpr NodeIndex nodeid0{0};
  static constexpr NodeIndex nodeid1{1};
  static constexpr NodeIndex nodeid2{2};
  static constexpr NodeIndex nodeid3{3};
  static constexpr NodeIndex nodeid4{4};
  static constexpr NodeIndex nodeid5{5};
  static constexpr NodeIndex nodeid6{6};
  static constexpr NodeIndex nodeid7{7};
  static constexpr NodeIndex nodeid8{8};
  static constexpr NodeIndex nodeid9{9};

  Graph graph;
  Node node0{false, nodeid0, "Frankfurt"};
  Node node1{false, nodeid1, "Mannheim"};
  Node node2{false, nodeid2, "Würzburg"};
  Node node3{false, nodeid3, "Kassel"};
  Node node4{false, nodeid4, "Karlsruhe"};
  Node node5{false, nodeid5, "Nürnberg"};
  Node node6{false, nodeid6, "Erfurt"};
  Node node7{false, nodeid7, "München"};
  Node node8{false, nodeid8, "Augsburg"};
  Node node9{false, nodeid9, "Stuttgart"};

  std::vector<Node> bfs_expected_node_container{
      node0, node1, node2, node3, node4, node5, node6, node7, node8, node9};
  std::vector<Node> bfs_node_container;

  graph.add_edge(nodeid0, "Frankfurt", nodeid1, "Mannheim");
  graph.add_edge(nodeid0, "Frankfurt", nodeid2, "Würzburg");
  graph.add_edge(nodeid0, "Frankfurt", nodeid3, "Kassel");
  graph.add_edge(nodeid1, "Mannheim", nodeid4, "Karlsruhe");
  graph.add_edge(nodeid2, "Würzburg", nodeid5, "Nürnberg");
  graph.add_edge(nodeid2, "Würzburg", nodeid6, "Erfurt");
  graph.add_edge(nodeid3, "Kassel", nodeid7, "München");
  graph.add_edge(nodeid4, "Karlsruhe", nodeid8, "Augsburg");
  graph.add_edge(nodeid5, "Nürnberg", nodeid9, "Stuttgart");

  graph.breadth_first_search(nodeid0, [&bfs_node_container](Node const& node) {
    bfs_node_container.push_back(node);
    return false;
  });
  ASSERT_EQ(bfs_node_container, bfs_expected_node_container);
}

// clang-format off
TEST(BreadthFirstSearchUndirectedTest, TestReturnEarly) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  // clang-format on

  static constexpr NodeIndex nodeid0{0};
  static constexpr NodeIndex nodeid1{1};
  static constexpr NodeIndex nodeid2{2};
  static constexpr NodeIndex nodeid3{3};
  static constexpr NodeIndex nodeid4{4};
  static constexpr NodeIndex nodeid5{5};
  static constexpr NodeIndex nodeid6{6};
  static constexpr NodeIndex nodeid7{7};
  static constexpr NodeIndex nodeid8{8};
  static constexpr NodeIndex nodeid9{9};

  Graph graph;
  Node node0{false, nodeid0, "Frankfurt"};
  Node node1{false, nodeid1, "Mannheim"};
  Node node2{false, nodeid2, "Würzburg"};
  Node node3{false, nodeid3, "Kassel"};
  Node node4{false, nodeid4, "Karlsruhe"};
  Node node5{false, nodeid5, "Nürnberg"};
  Node node6{false, nodeid6, "Erfurt"};
  Node node7{false, nodeid7, "München"};
  Node node8{false, nodeid8, "Augsburg"};
  Node node9{false, nodeid9, "Stuttgart"};

  std::stringstream ss;
  ss << node0 << ", " << node1;
  ASSERT_STREQ(ss.str().c_str(),
               "Node ID: 0 = Frankfurt, Node ID: 1 = Mannheim");

  std::vector<Node> bfs_expected_node_container{node0, node1, node2,
                                                node3, node4, node5};
  std::vector<Node> bfs_node_container;

  graph.add_edge(nodeid0, "Frankfurt", nodeid1, "Mannheim");
  graph.add_edge(nodeid0, "Frankfurt", nodeid2, "Würzburg");
  graph.add_edge(nodeid0, "Frankfurt", nodeid3, "Kassel");
  graph.add_edge(nodeid1, "Mannheim", nodeid4, "Karlsruhe");
  graph.add_edge(nodeid2, "Würzburg", nodeid5, "Nürnberg");
  graph.add_edge(nodeid2, "Würzburg", nodeid6, "Erfurt");
  graph.add_edge(nodeid3, "Kassel", nodeid7, "München");
  graph.add_edge(nodeid4, "Karlsruhe", nodeid8, "Augsburg");
  graph.add_edge(nodeid5, "Nürnberg", nodeid9, "Stuttgart");

  graph.breadth_first_search(nodeid0, [&bfs_node_container](Node const& node) {
    bfs_node_container.push_back(node);
    if (node.key() == nodeid5) return true;
    return false;
  });

  ASSERT_EQ(bfs_node_container, bfs_expected_node_container);
}

}  // namespace
