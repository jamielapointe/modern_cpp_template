#include <gtest/gtest.h>
#include <myproject/fibonacci.h>

using myproject::algorithms::fibonacci;

TEST(FibonacciTest, Basic00) {
  ASSERT_EQ(fibonacci(-500), -500);
  ASSERT_EQ(fibonacci(0), 0);
  ASSERT_EQ(fibonacci(1), 1);
  ASSERT_EQ(fibonacci(2), 1);
  ASSERT_EQ(fibonacci(3), 2);
  ASSERT_EQ(fibonacci(4), 3);
  ASSERT_EQ(fibonacci(5), 5);
  ASSERT_EQ(fibonacci(6), 8);
  ASSERT_EQ(fibonacci(7), 13);
  ASSERT_EQ(fibonacci(8), 21);
  ASSERT_EQ(fibonacci(9), 34);
  ASSERT_EQ(fibonacci(10), 55);
  ASSERT_EQ(fibonacci(11), 89);
  ASSERT_EQ(fibonacci(26), 121393);
  ASSERT_EQ(fibonacci(55), 139583862445);
}
