///\file fibonacci.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief Compute the fibonacci series
///\version 0.1
///\date 2023-06-25
///
///\copyright Copyright (c) 2023
///

#pragma once

#include <array>
#include <cstdint>
#include <gsl/gsl>
#include <initializer_list>
#include <utility>
#include <variant>

#include "modern_cpp_template/binary_exponentiation.h"
#include "modern_cpp_template/macros.h"

namespace modern_cpp_template::algorithms {

namespace internal {

///\brief The maximum number that can be passed into the fibonacci function
static constexpr int64_t kMaxFibonacciNumber{92};
///\brief The maximum number that can be passed into the fibonacci_fast1
static constexpr int64_t kMaxFibonacciFast1Number{63};
///\brief The maximum number that can be passed into the fibonacci_fast2
static constexpr int64_t kMaxFibonacciFast2Number{92};

///\brief This is a ridiculously simple Matrix just to support the
/// fibonacci_fast1_internal algorithm
/// This is \b NOT meant to be used for anything other than the
/// fibonacci_fast1_internal algorithm. There are much better linear algebra
/// constructs out there such as Eigen:
/// https://eigen.tuxfamily.org/index.php?title=Main_Page
///\tparam Tp The type of the Matrix such as double, int64_t, etc.
template <typename Tp>
class Simple_Fibonacci_Matrix_2_2 {
 public:
  static constexpr int kNumCols{2};
  static constexpr int kNumRows{2};
  static constexpr int kLinearSize{kNumCols * kNumRows};

  using Matrix_Data = std::array<std::array<Tp, kNumCols>, kNumRows>;
  using Array_Data = std::array<Tp, kLinearSize>;
  using Index = gsl::index;

  ///\brief constexpr constructor taking in 4 values to fill in the Matrix
  ///
  ///\param a value for cell 0
  ///\param b value for cell 1
  ///\param c value for cell 2
  ///\param d value for cell 3
  constexpr Simple_Fibonacci_Matrix_2_2(Tp a, Tp b, Tp c, Tp d)
      : m_data{Matrix_Data{{{a, b}, {c, d}}}} {}

  // One does not declare explicit for a std::initializer_list Constructor
  ///\brief construct a new Simple_Fibonacci_Matrix_2_2
  constexpr Simple_Fibonacci_Matrix_2_2(
      std::initializer_list<std::initializer_list<Tp>> const &list) {
    size_t list_size{0};
    if (list.begin() != list.end()) {
      list_size = list.begin()->size();
    }
    modern_cpp_template_assert_message(
        list.size() == static_cast<size_t>(kNumRows),
        "The first dimension of list does not contain the proper "
        "number of rows");
    modern_cpp_template_assert_message(
        list_size == static_cast<size_t>(kNumCols),
        "The second dimension of list does not contain "
        "the proper number of columns");
    Index row_index{0};
    for (auto const &row : list) {
      modern_cpp_template_assert(list_size == row.size());
      Index col_index{0};
      for (auto const &list_val : row) {
        coeff(row_index, col_index) = list_val;
        ++col_index;
      }
      ++row_index;
    }
  }

  ///\brief construct a new Simple_Fibonacci_Matrix_2_2
  constexpr explicit Simple_Fibonacci_Matrix_2_2(Matrix_Data const &&data_in)
      : m_data(data_in) {}

  ///\brief construct a new Simple_Fibonacci_Matrix_2_2
  constexpr explicit Simple_Fibonacci_Matrix_2_2(Matrix_Data const &data_in)
      : m_data(data_in) {}

  ///\brief construct a new Simple_Fibonacci_Matrix_2_2
  constexpr explicit Simple_Fibonacci_Matrix_2_2(Array_Data const &&data_in)
      : m_data(data_in) {}

  ///\brief construct a new Simple_Fibonacci_Matrix_2_2
  constexpr explicit Simple_Fibonacci_Matrix_2_2(Array_Data const &data_in)
      : m_data(data_in) {}

  ///\brief static constexpr number of rows of the Matrix
  ///
  ///\return constexpr int
  static constexpr int rows() { return kNumRows; }

  ///\brief static constexpr number of columns of the Matrix
  ///
  ///\return constexpr int
  static constexpr int cols() { return kNumCols; }

  ///\brief static constexpr size or length of the Matrix
  ///
  ///\return constexpr int
  static constexpr int size() { return kLinearSize; }

  ///\brief Return the 2D array representation of the Matrix
  ///
  ///\return Matrix_Data const& constant reference to the 2D data
  Matrix_Data const &matrix_data() const {
    return std::get<Matrix_Data>(m_data);
  }

  ///\brief Return the 1D array representation of the Matrix
  ///
  ///\return Array_Data const& constant reference to the 1D data
  Array_Data const &array_data() const { return std::get<Array_Data>(m_data); }

  ///\brief Return the value of the Matrix cell value
  /// There is no runtime assert that the row is in range!
  ///\param row The row into the 2D matrix
  ///\param col The col into the 2D matrix
  ///\return Tp value of the Matrix cell at row,col index
  Tp coeff(Index row, Index col) const {
    modern_cpp_template_internal_assert(row >= 0 && row < rows() && col >= 0 &&
                                        col < cols());
    return matrix_data()[static_cast<size_t>(row)][static_cast<size_t>(col)];
  }

  ///\brief Return the value of the Matrix cell value
  /// There is a runtime assert that row is in range (debug only)
  ///\param row The row into the 2D matrix
  ///\param col The col into the 2D matrix
  ///\return Tp value of the Matrix cell at row,col index
  Tp operator()(Index row, Index col) const {
    modern_cpp_template_assert(row >= 0 && row < rows() && col >= 0 &&
                               col < cols());
    return coeff(row, col);
  }

  ///\brief Return a reference to the Matrix cell value
  /// There is no runtime assert that the row is in range!
  ///\param row The row into the 2D matrix
  ///\param col The col into the 2D matrix
  ///\return Tp& reference the Matrix cell at row,col index
  Tp &coeff(Index row, Index col) {
    modern_cpp_template_internal_assert(row >= 0 && row < rows() && col >= 0 &&
                                        col < cols());
    return matrix_data()[static_cast<size_t>(row)][static_cast<size_t>(col)];
  }

  ///\brief Return a reference to the Matrix cell value
  /// There is a runtime assert that row is in range (debug only)
  ///\param row The row into the 2D matrix
  ///\param col The col into the 2D matrix
  ///\return Tp& reference the Matrix cell at row,col index
  Tp &operator()(Index row, Index col) {
    modern_cpp_template_assert(row >= 0 && row < rows() && col >= 0 &&
                               col < cols());
    return coeff(row, col);
  }

  ///\brief Return value of the Matrix cell value
  /// There is no runtime assert that the row is in range!
  ///\param index The 1D index into the matrix
  ///\return Tp value of the Matrix cell at index
  Tp coeff(Index index) const {
    modern_cpp_template_internal_assert(index >= 0 && index < size());
    return array_data()[index];
  }

  ///\brief Return value of the Matrix cell value
  /// There is a runtime assert that row is in range (debug only)
  ///\param index The 1D index into the matrix
  ///\return Tp value of the Matrix cell at index
  Tp operator()(Index index) const {
    modern_cpp_template_assert(index >= 0 && index < size());
    return coeff(index);
  }

  ///\brief Return a reference to the Matrix cell value
  /// There is no runtime assert that the row is in range!
  ///\param index The 1D index into the matrix
  ///\return Tp& reference the Matrix cell at index
  Tp &coeff(Index index) {
    modern_cpp_template_internal_assert(index >= 0 && index < size());
    return array_data()[index];
  }

  ///\brief Return a reference to the Matrix cell value
  /// There is a runtime assert that row is in range (debug only)
  ///\param index The 1D index into the matrix
  ///\return Tp& reference the Matrix cell at index
  Tp &operator()(Index index) {
    modern_cpp_template_assert(index >= 0 && index < size());
    return coeff(index);
  }

  ///\brief return the zero matrix
  ///\return constexpr Simple_Fibonacci_Matrix_2_2
  static constexpr Simple_Fibonacci_Matrix_2_2 zero() {
    return Simple_Fibonacci_Matrix_2_2{0, 0, 0, 0};
  }

  ///\brief return the identity matrix
  ///\return constexpr Simple_Fibonacci_Matrix_2_2
  static constexpr Simple_Fibonacci_Matrix_2_2 identity() {
    return Simple_Fibonacci_Matrix_2_2{1, 0, 0, 1};
  }

  ///\brief Multiply two Simple_Fibonacci_Matrix_2_2 objects
  /// This is just simple 2x2 matrix multiplication operation
  ///\param lhs The left hand side matrix
  ///\param rhs The right hand side matrix
  ///\return Simple_Fibonacci_Matrix_2_2 the resultant matrix
  Simple_Fibonacci_Matrix_2_2 friend operator*(
      Simple_Fibonacci_Matrix_2_2 const &lhs,
      Simple_Fibonacci_Matrix_2_2 const &rhs) {
    return Simple_Fibonacci_Matrix_2_2{
        lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0),
        lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1),
        lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0),
        lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1)};
  }

 private:
  ///\brief The data of the matrix
  /// The data of the matrix can be represented as 2x2 array or a 1D array of
  /// length 4
  std::variant<Matrix_Data, Array_Data> m_data;

  Matrix_Data &matrix_data() { return std::get<Matrix_Data>(m_data); }

  Array_Data &array_data() { return std::get<Array_Data>(m_data); }
};

///\brief Compute the n'th Fibonacci sequence for an integer
/// Let number = \f$a\f$.  If \f$a \le 1 \f$a, then return \f$a\f$ else return
/// the proper fibonacci series: let \f$F_n\f$ be the fibonacci series for index
/// \f$n\f$, then \f$F_n = F_{n-1} + F_{n+2}\f$.
/// This is the fast implementation and has time complexity of
/// \f$\mathcal{O}\left(\log{}n\right)\f$
///\param number the n'th sequence of the Fibonacci numbers
///\return constexpr std::pair<int64_t, int64_t> return the \f$F_n and
/// F_{n+1}\f$ pair of Fibonacci numbers
inline int64_t fibonacci_fast1_internal(int64_t number) noexcept {
  Simple_Fibonacci_Matrix_2_2<int64_t> base{{1, 1}, {1, 0}};
  return modern_cpp_template::algorithms::matrix_exponentiation(base, number)(
      0, 1);
}

///\brief Compute the n'th Fibonacci sequence for an integer
/// Let number = \f$a\f$.  If \f$a \le 1 \f$a, then return \f$a\f$ else return
/// the proper fibonacci series: let \f$F_n\f$ be the fibonacci series for index
/// \f$n\f$, then \f$F_n = F_{n-1} + F_{n+2}\f$.
/// This is the fast implementation and has time complexity of
/// \f$\mathcal{O}\left(\log{}n\right)\f$
///\param number the n'th sequence of the Fibonacci numbers
///\return constexpr std::pair<int64_t, int64_t> return the \f$F_n and
/// F_{n+1}\f$ pair of Fibonacci numbers
inline constexpr std::pair<int64_t, int64_t> fibonacci_fast2_internal(
    int64_t number) noexcept {
  if (number == 0) return {0, 1};

  auto p = fibonacci_fast2_internal(number >> 1);
  auto c = p.first * (2 * p.second - p.first);
  auto d = p.first * p.first + p.second * p.second;
  if (number & 1) return {d, c + d};
  return {c, d};
}

}  // namespace internal

///\brief Compute the n'th Fibonacci sequence for an integer
/// Let number = \f$a\f$.  If \f$a \le 1 \f$a, then return \f$a\f$ else return
/// the proper fibonacci series: let \f$F_n\f$ be the fibonacci series for index
/// \f$n\f$, then \f$F_n = F_{n-1} + F_{n+2}\f$.
/// This is the naive implementation has time complexity of
/// \f$ \mathcal{O}\left(n\right) \f$
///\param number the n'th sequence of the Fibonacci numbers
///\return constexpr int64_t If \f$a \le 1 \f$a, then return \f$a\f$ else return
/// the proper fibonacci series
inline constexpr int64_t fibonacci(int64_t number) {
  if (number <= 1) return number;
  modern_cpp_template_assert_message(
      number <= internal::kMaxFibonacciNumber,
      "number will cause a signed integer overflow");

  int64_t previous_iteration_one{0};
  int64_t previous_iteration_zero{1};
  int64_t current_iteration{0};
  for (int64_t i = 2; i <= number; ++i) {
    current_iteration = previous_iteration_one + previous_iteration_zero;
    previous_iteration_one = previous_iteration_zero;
    previous_iteration_zero = current_iteration;
  }
  return current_iteration;
}

///\brief Compute the n'th Fibonacci sequence for an integer
/// Let number = \f$a\f$.  If \f$a \le 1 \f$a, then return \f$a\f$ else return
/// the proper fibonacci series: let \f$F_n\f$ be the fibonacci series for index
/// \f$n\f$, then \f$F_n = F_{n-1} + F_{n+2}\f$.
/// This is the fast implementation and has time complexity of
/// \f$\mathcal{O}\left(\log{}n\right)\f$
///\param number the n'th sequence of the Fibonacci numbers
///\return constexpr the \f$F_n\f$ Fibonacci number
inline constexpr int64_t fibonacci_fast1(int64_t number) noexcept {
  if (number <= 1) return number;
  modern_cpp_template_assert_message(
      number <= internal::kMaxFibonacciFast1Number,
      "number will cause a signed integer overflow");

  return internal::fibonacci_fast1_internal(number);
}

///\brief Compute the n'th Fibonacci sequence for an integer
/// Let number = \f$a\f$.  If \f$a \le 1 \f$a, then return \f$a\f$ else return
/// the proper fibonacci series: let \f$F_n\f$ be the fibonacci series for index
/// \f$n\f$, then \f$F_n = F_{n-1} + F_{n+2}\f$.
/// This is the fast implementation and has time complexity of
/// \f$\mathcal{O}\left(\log{}n\right)\f$
///\param number the n'th sequence of the Fibonacci numbers
///\return constexpr the \f$F_n\f$ Fibonacci number
inline constexpr int64_t fibonacci_fast2(int64_t number) noexcept {
  if (number <= 1) return number;
  modern_cpp_template_assert_message(
      number <= internal::kMaxFibonacciFast2Number,
      "number will cause a signed integer overflow");

  return internal::fibonacci_fast2_internal(number - 1).second;
}

}  // namespace modern_cpp_template::algorithms
