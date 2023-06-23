
#pragma once

#include <cstdint>

namespace myproject::algorithms {

[[nodiscard]] constexpr int64_t fibonacci(int64_t number) noexcept {
  int64_t previous_iteration_one{0};
  int64_t previous_iteration_zero{1};
  int64_t current_iteration{0};
  if (number <= 1) {
    return number;
  }
  for (int64_t i = 2; i <= number; ++i) {
    current_iteration = previous_iteration_one + previous_iteration_zero;
    previous_iteration_one = previous_iteration_zero;
    previous_iteration_zero = current_iteration;
  }
  return current_iteration;
}

}  // namespace myproject::algorithms
