#ifndef SAMPLE_LIBRARY_HPP
#define SAMPLE_LIBRARY_HPP

[[nodiscard]] constexpr int factorial(int input) noexcept {
  if (input == 0) {
    return 1;
  }

  return input * factorial(input - 1);
}

#endif
