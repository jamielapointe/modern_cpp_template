#include <gtest/gtest.h>

#include "gtest/gtest.h"
#include "modern_cpp_template/fibonacci.h"
#include "modern_cpp_template_config.h"

using modern_cpp_template::algorithms::fibonacci;
using modern_cpp_template::algorithms::fibonacci_fast1;
using modern_cpp_template::algorithms::fibonacci_fast2;

TEST(FibonacciTest, FibonacciTest00) {
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
  ASSERT_EQ(fibonacci(16), 987);
  ASSERT_EQ(fibonacci(28), 317811);
  ASSERT_EQ(fibonacci(56), 225851433717);
  ASSERT_EQ(fibonacci(64), 10610209857723);
  ASSERT_EQ(fibonacci(91), 4660046610375530309);
  ASSERT_EQ(fibonacci(92), 7540113804746346429);
  ASSERT_EXIT(fibonacci(93), testing::KilledBySignal(SIGABRT), "");
}

TEST(FibonacciTest, FibonacciFast1Test00) {
  ASSERT_EQ(fibonacci_fast1(-500), -500);
  ASSERT_EQ(fibonacci_fast1(0), 0);
  ASSERT_EQ(fibonacci_fast1(1), 1);
  ASSERT_EQ(fibonacci_fast1(2), 1);
  ASSERT_EQ(fibonacci_fast1(3), 2);
  ASSERT_EQ(fibonacci_fast1(4), 3);
  ASSERT_EQ(fibonacci_fast1(5), 5);
  ASSERT_EQ(fibonacci_fast1(6), 8);
  ASSERT_EQ(fibonacci_fast1(7), 13);
  ASSERT_EQ(fibonacci_fast1(8), 21);
  ASSERT_EQ(fibonacci_fast1(9), 34);
  ASSERT_EQ(fibonacci_fast1(10), 55);
  ASSERT_EQ(fibonacci_fast1(16), 987);
  ASSERT_EQ(fibonacci_fast1(28), 317811);
  ASSERT_EQ(fibonacci_fast1(56), 225851433717);
  ASSERT_EQ(fibonacci_fast1(63), 6557470319842);
  ASSERT_EXIT(fibonacci_fast1(64), testing::KilledBySignal(SIGABRT), "");
}

TEST(FibonacciTest, FibonacciFast2Test00) {
  ASSERT_EQ(fibonacci_fast2(-500), -500);
  ASSERT_EQ(fibonacci_fast2(0), 0);
  ASSERT_EQ(fibonacci_fast2(1), 1);
  ASSERT_EQ(fibonacci_fast2(2), 1);
  ASSERT_EQ(fibonacci_fast2(3), 2);
  ASSERT_EQ(fibonacci_fast2(4), 3);
  ASSERT_EQ(fibonacci_fast2(5), 5);
  ASSERT_EQ(fibonacci_fast2(6), 8);
  ASSERT_EQ(fibonacci_fast2(7), 13);
  ASSERT_EQ(fibonacci_fast2(8), 21);
  ASSERT_EQ(fibonacci_fast2(9), 34);
  ASSERT_EQ(fibonacci_fast2(10), 55);
  ASSERT_EQ(fibonacci_fast2(16), 987);
  ASSERT_EQ(fibonacci_fast2(28), 317811);
  ASSERT_EQ(fibonacci_fast2(56), 225851433717);
  ASSERT_EQ(fibonacci_fast2(64), 10610209857723);
  ASSERT_EQ(fibonacci_fast2(91), 4660046610375530309);
  ASSERT_EQ(fibonacci_fast2(92), 7540113804746346429);
  ASSERT_EXIT(fibonacci_fast2(93), testing::KilledBySignal(SIGABRT), "");
}
