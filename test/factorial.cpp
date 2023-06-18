#include <gtest/gtest.h>
#include <myproject/factorial.h>

TEST(FactorialTest, HandlesPositiveInput) {
  STATIC_REQUIRE(factorial(0) == 1);
  STATIC_REQUIRE(factorial(1) == 1);
  STATIC_REQUIRE(factorial(2) == 2);
  STATIC_REQUIRE(factorial(3) == 6);
  STATIC_REQUIRE(factorial(10) == 3628800);
}
