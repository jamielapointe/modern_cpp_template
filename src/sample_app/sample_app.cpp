#include "myproject/fibonacci.h"
#include "myproject/undirected_graph.h"
#include "myproject_config.h"

using myproject::algorithms::fibonacci;
using myproject::algorithms::fibonacci_fast1;
using myproject::algorithms::fibonacci_fast2;

namespace myproject::myproject_sample_app {

void run_sample_app() {
  static constexpr int kFibonacciTooHigh{93};
  static constexpr int kFibonacciFast1TooHigh{93};
  fibonacci(kFibonacciTooHigh);
  fibonacci_fast1(kFibonacciFast1TooHigh);
  fibonacci_fast2(kFibonacciTooHigh);
}

}  // namespace myproject::myproject_sample_app

int main() {
  myproject::myproject_sample_app::run_sample_app();
  return 0;
}
