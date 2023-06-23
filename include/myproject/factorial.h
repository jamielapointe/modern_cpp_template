#pragma once

#include <cstdint>

namespace myproject::algorithms {

[[nodiscard]] constexpr int64_t factorial(int64_t number) noexcept {
  int64_t result{1};
  while (number > 0) {
    result *= number;
    --number;
  }
  return result;
}

}  // namespace myproject::algorithms
