#include <gtest/gtest.h>

#include <array>
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

static int fibonacciIterative(int n)
{
    //! Initialize n - 2 and n - 1 Fibonacci numbers
    int n_2 {0};
    if (0 == n)
    {
        return n_2;
    }
    
    int n_1 {1};
    if (1 == n)
    {
        return n_1;
    }

    int fib_at_i {};
    for (int i = 2; i <= n; ++i)
    {
        fib_at_i = n_1 + n_2;
        n_2      = n_1;
        n_1      = fib_at_i;
    }
    
    return fib_at_i;

} // static int fibonacciIterative( ...

//! @brief Iterative solution from HR discussion section
static int fibonacciDSIterative(int n)
{
    //! @details O(n) time complexity, O(1) space complexity

    std::array<int, 2> fib {{0, 1}};

    for (int i = 0; i <= n; ++i)
    {
        fib[i % 2] = fib[0] + fib[1];
    }
    
    return fib[n % 2];

} // static int fibonacciDSIterative( ...

// Test case 2
TEST(FibonacciTest, TestCase2) {
    EXPECT_EQ(5, fibonacci(5));
    EXPECT_EQ(5, fibonacciMemoized(5));
    EXPECT_EQ(5, fibonacciIterative(5));
    EXPECT_EQ(5, fibonacciDSIterative(5));
}

// Test case 4
TEST(FibonacciTest, TestCase4) {
    EXPECT_EQ(144, fibonacci(12));
    EXPECT_EQ(144, fibonacciMemoized(12));
    EXPECT_EQ(144, fibonacciIterative(12));
    EXPECT_EQ(144, fibonacciDSIterative(12));
}