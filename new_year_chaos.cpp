#include <gtest/gtest.h>

#include <iostream>

// Basic assertions to verify setup works
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expet equality.
  EXPECT_EQ(7 * 6, 42);
}