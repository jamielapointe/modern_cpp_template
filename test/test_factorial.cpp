#include <gtest/gtest.h>
#include <modern_cpp_template/factorial.h>

using modern_cpp_template::algorithms::factorial;

TEST(FactorialTest, Basic00) {
  ASSERT_EQ(factorial(0), 1);
  ASSERT_EQ(factorial(1), 1);
  ASSERT_EQ(factorial(2), 2);
  ASSERT_EQ(factorial(3), 6);
  ASSERT_EQ(factorial(10), 3628800);
}
