#include <gtest/gtest.h>

static int fibonacci(int n)
{
    if (0 == n)
    {
        return 0;
    }
    if (1 == n)
    {
        return 1;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);

} // static int fibonacci( ...

// Test case 2
TEST(FibonacciTest, TestCase2) {
    EXPECT_EQ(5, fibonacci(5));
}

// Test case 4
TEST(FibonacciTest, TestCase4) {
    EXPECT_EQ(144, fibonacci(12));
}