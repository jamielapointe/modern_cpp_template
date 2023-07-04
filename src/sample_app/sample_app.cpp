#include "myproject/undirected_graph.h"

namespace myproject::myproject_sample_app {

void run_sample_app() {
  // do something
  // something else

  // Remember to catch a possible exception when calling either get_edge_nodes
  // or bfs try {
  //   node_children = get_edge_nodes(node);
  // } catch (std::logic_error const& exc) {
  //   std::cerr << "Out of range error: " << exc.what() << '\n';
  //   return;
  // }
}

}  // namespace myproject::myproject_sample_app

int main() {
  myproject::myproject_sample_app::run_sample_app();
  return 0;
}