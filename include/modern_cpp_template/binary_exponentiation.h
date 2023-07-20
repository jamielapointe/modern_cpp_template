///\file binary_exponentiation.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief Binary exponentiation is a trick which allows you to calculate
///
/// \f$a^n\f$ using only \f$\mathcal{O}\left(\log{}n\right)\f$ multiplications
/// instead of \f$\mathcal{O}\left(n\right)\f$ multiplications required by the
/// naive approach.  This is also known as exponentiation by squaring.
///
/// More information: https://cp-algorithms.com/algebra/binary-exp.html
///
///\version 0.1
///\date 2023-07-01
///
///\copyright Copyright (c) 2023
///

#pragma once

#include <array>
#include <cstdint>

///\brief the modern_cpp_template::algorithms namespace
/// This is the namespace for all algorithms in the modern_cpp_template library
/// Many of which are just inline functions
namespace modern_cpp_template::algorithms {

///\brief binary exponentiation
/// Compute \f$x^n \mod m\f$
///\param base is the base variable \f$x\f$
///\param exponent is the exponent variable \f$n\f$
///\param modulus is the modulus variable \f$m\f$
///\return the result of the computation as an int64_t
inline int64_t binary_exponentiation(int64_t base, int64_t exponent,
                                     int64_t modulus) {
  base %= modulus;
  int64_t result = 1;
  while (exponent > 0) {
    std::array<int64_t, 2> x = {result, result * base % modulus};
    // clang-format off
    result = x[exponent & 1]; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    // clang-format on
    base = base * base % modulus;
    exponent >>= 1;
  }
  return result;
}

///\brief matrix exponentiation
/// Compute \f$X^n\f$ where X is a matrix and n is an integer
///\tparam Mat The Matrix Type that supports \c identity function and
/// \c operator*
///\param base is the Matrix base variable \f$x\f$
///\param exponent is the integer exponent variable \f$n\f$
///\return the result of the computation as a Matrix
template <typename Mat>
inline Mat matrix_exponentiation(Mat base, int64_t exponent) {
  Mat answer = Mat::identity();
  while (exponent != 0) {
    std::array<Mat, 2> x = {answer, (answer * base)};
    // clang-format off
    answer = x[exponent & 1]; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    // clang-format on
    base = (base * base);
    exponent >>= 1;
  }
  return answer;
}

}  // namespace modern_cpp_template::algorithms
