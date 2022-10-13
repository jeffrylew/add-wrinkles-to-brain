#include <gtest/gtest.h>

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

// Test case 0
TEST(StepPermsTest, TestCase0) {
    EXPECT_EQ(1, stepPermsFirstAttempt(1));
    EXPECT_EQ(4, stepPermsFirstAttempt(3));
    EXPECT_EQ(44, stepPermsFirstAttempt(7));
}

// Test case 9
TEST(StepPermsTest, TestCase9) {
    EXPECT_EQ(13, stepPermsFirstAttempt(5));
    EXPECT_EQ(81, stepPermsFirstAttempt(8));
}

// Test case 10
TEST(StepPermsTest, TestCase10) {
    EXPECT_EQ(5768, stepPermsFirstAttempt(15));
    EXPECT_EQ(121415, stepPermsFirstAttempt(20));
    EXPECT_EQ(8646064, stepPermsFirstAttempt(27));
}