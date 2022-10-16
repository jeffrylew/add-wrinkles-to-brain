#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

//! @brief Recursive helper function for first attempt solution
//! @param[in]  n                 Number of stairs in the staircase
//! @param[out] num_ways_to_climb Reference to int for number of ways to climb
static void stepPermsFirstAttempt(int n, int& num_ways_to_climb)
{
    if (n < 0)
    {
        return;
    }
    if (n == 0)
    {
        //! Increment number of ways Davis can climb staircase, modulo 10^10 + 7
        num_ways_to_climb = (1 + num_ways_to_climb) % 10000000007;
        return;
    }
    stepPermsFirstAttempt(n - 1, num_ways_to_climb);
    stepPermsFirstAttempt(n - 2, num_ways_to_climb);
    stepPermsFirstAttempt(n - 3, num_ways_to_climb);

} // static void stepPermsFirstAttempt( ...

//! @brief First attempt solution times out for Test cases 5-8 but passes others
static int stepPermsFirstAttempt(int n)
{
    int num_ways_to_climb {};
    stepPermsFirstAttempt(n, num_ways_to_climb);
    return num_ways_to_climb;
}

//! @brief Recursive helper function with memoization for discussion solution
//! @param[in] n     Number of stairs in the staircase
//! @param[out] cache Reference to map<number of stairs, number ways to climb>
static int stepPermsMemoize(int n, std::unordered_map<int, int>& cache)
{
    if (1 == n)
    {
        return 1;
    }
    if (2 == n)
    {
        return 2;
    }
    if (3 == n)
    {
        return 4;
    }
    if (0 == cache.count(n))
    {
        cache[n] = stepPermsMemoize(n - 1, cache) //
                 + stepPermsMemoize(n - 2, cache) //
                 + stepPermsMemoize(n - 3, cache);
    }
    return cache[n];

} // static int stepPermsMemoize( ...

//! @brief Recursion with memoization solution from HR discussion section
//! @param[in] n Number of stairs in the staircase
//! @return Number of ways Davis can climb staircase
static int stepPermsMemoize(int n)
{
    //! @details
    //!     https://www.hackerrank.com/challenges/ctci-recursive-staircase/forum

    std::unordered_map<int, int> cache {};
    return stepPermsMemoize(n, cache);
}

//! @brief Dynamic programming solution from HR discussion section
//! @param[in] n Number of stairs in the staircase
//! @return Number of ways Davis can climb staircase
static int stepPermsDP(int n)
{
    //! @details
    //!     https://www.hackerrank.com/challenges/ctci-recursive-staircase/forum
    //!
    //! O(n) time complexity, O(n) space complexity

    std::vector<int> dp(static_cast<std::size_t>(std::max(n + 1, 4)));
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    for (int i = 4; i < n + 1; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }
    
    return dp[n];

} // static int stepPermsDP( ...

//! @brief Optimized dynamic programming solution from HR discussion section
//! @param[in] n Number of stairs in the staircase
//! @return Number of ways Davis can climb staircase
static int stepPermsDPOptimized(int n)
{
    //! @details
    //!     https://www.hackerrank.com/challenges/ctci-recursive-staircase/forum
    //!
    //! O(n) time complexity, O(1) space complexity

    std::vector<int> dp {1, 2, 4};

    if (n > 0 && n < 4)
    {
        return dp[n - 1];
    }
    
    for (int i = 3; i < n; ++i)
    {
        dp[i % 3] = dp[0] + dp[1] + dp[2];
    }
    
    return dp[(n - 1) % 3];

} // static int stepPermsDPOptimized( ...

// Test case 0
TEST(StepPermsTest, TestCase0) {
    EXPECT_EQ(1, stepPermsFirstAttempt(1));
    EXPECT_EQ(4, stepPermsFirstAttempt(3));
    EXPECT_EQ(44, stepPermsFirstAttempt(7));

    EXPECT_EQ(1, stepPermsMemoize(1));
    EXPECT_EQ(4, stepPermsMemoize(3));
    EXPECT_EQ(44, stepPermsMemoize(7));

    EXPECT_EQ(1, stepPermsDP(1));
    EXPECT_EQ(4, stepPermsDP(3));
    EXPECT_EQ(44, stepPermsDP(7));

    EXPECT_EQ(1, stepPermsDPOptimized(1));
    EXPECT_EQ(4, stepPermsDPOptimized(3));
    EXPECT_EQ(44, stepPermsDPOptimized(7));
}

// Test case 9
TEST(StepPermsTest, TestCase9) {
    EXPECT_EQ(13, stepPermsFirstAttempt(5));
    EXPECT_EQ(81, stepPermsFirstAttempt(8));

    EXPECT_EQ(13, stepPermsMemoize(5));
    EXPECT_EQ(81, stepPermsMemoize(8));

    EXPECT_EQ(13, stepPermsDP(5));
    EXPECT_EQ(81, stepPermsDP(8));

    EXPECT_EQ(13, stepPermsDPOptimized(5));
    EXPECT_EQ(81, stepPermsDPOptimized(8));
}

// Test case 10
TEST(StepPermsTest, TestCase10) {
    EXPECT_EQ(5768, stepPermsFirstAttempt(15));
    EXPECT_EQ(121415, stepPermsFirstAttempt(20));
    EXPECT_EQ(8646064, stepPermsFirstAttempt(27));

    EXPECT_EQ(5768, stepPermsMemoize(15));
    EXPECT_EQ(121415, stepPermsMemoize(20));
    EXPECT_EQ(8646064, stepPermsMemoize(27));

    EXPECT_EQ(5768, stepPermsDP(15));
    EXPECT_EQ(121415, stepPermsDP(20));
    EXPECT_EQ(8646064, stepPermsDP(27));

    EXPECT_EQ(5768, stepPermsDPOptimized(15));
    EXPECT_EQ(121415, stepPermsDPOptimized(20));
    EXPECT_EQ(8646064, stepPermsDPOptimized(27));
}