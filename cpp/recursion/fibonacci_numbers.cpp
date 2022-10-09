#include <gtest/gtest.h>

#include <map>
#include <tuple>

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

static int fibonacciMemoized(int n, std::map<int, int>& fib_map)
{
    if (fib_map.count(n) > 0)
    {
        return fib_map.at(n);
    }

    const auto n_1 = fibonacciMemoized(n - 1, fib_map);
    std::ignore    = fib_map.emplace(n - 1, n_1);

    const auto n_2 = fibonacciMemoized(n - 2, fib_map);
    std::ignore    = fib_map.emplace(n - 2, n_2);
    
    return n_1 + n_2;

} // static int fibonacciMemoized( ...

static int fibonacciMemoized(int n)
{
    //! Map storing <n, corresponding Fibonacci number at n>
    std::map<int, int> fib_map {};

    //! Add cases for n = 0 and 1
    std::ignore = fib_map.emplace(0, 0);
    std::ignore = fib_map.emplace(1, 1);

    return fibonacciMemoized(n, fib_map);
}

// Test case 2
TEST(FibonacciTest, TestCase2) {
    EXPECT_EQ(5, fibonacci(5));
    EXPECT_EQ(5, fibonacciMemoized(5));
}

// Test case 4
TEST(FibonacciTest, TestCase4) {
    EXPECT_EQ(144, fibonacci(12));
    EXPECT_EQ(144, fibonacciMemoized(12));
}