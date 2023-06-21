#include <gtest/gtest.h>

#include "myproject/factorial.h"

namespace {

TEST(FactorialTest, Basic00) {
  ASSERT_EQ(factorial(0), 1);
  ASSERT_EQ(factorial(1), 1);
  ASSERT_EQ(factorial(2), 2);
  ASSERT_EQ(factorial(3), 6);
  ASSERT_EQ(factorial(10), 3628800);
}

}  // namespace
