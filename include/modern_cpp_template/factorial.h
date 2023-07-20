///\file factorial.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief A simple constexpr non-recursive factorial function
///\version 0.1
///\date 2023-06-25
///
///\copyright Copyright (c) 2023
///

#pragma once

#include <cstdint>

namespace modern_cpp_template::algorithms {

///\brief Compute the factorial of an integer
/// Compute \f$a!\f$ where \f$a\f$ is an integer.  Note that \f$0!=1\f$.  In
// this implementation if the user passes in a negative number, then 1 is just
// returned.
///\param number an integer - expected to be a positive number
///\return constexpr int64_t let \f$a\f$ = number, then if \f$a \le 1\f$ return
/// 1; else return \f$a!\f$.
[[nodiscard]] inline constexpr int64_t factorial(int64_t number) noexcept {
  int64_t result{1};
  while (number > 0) {
    result *= number;
    --number;
  }
  return result;
}

}  // namespace modern_cpp_template::algorithms
