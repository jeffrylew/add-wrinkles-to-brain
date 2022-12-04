#include <gtest/gtest.h>

#include <cmath>
#include <string>

//! @brief First attempt solution to determine if input n is prime
//! @param[in] n An integer to test for primality
// @return std::string containing Prime if n is prime, else Not prime
static std::string primalityFA(int n)
{
    if (1 == n)
    {
        return "Not prime";
    }

    const auto max_factor = static_cast<int>(std::floor(std::sqrt(n)));

    for (int factor = 2; factor <= max_factor; ++factor)
    {
        if (0 == n % factor)
        {
            return "Not prime";
        }
    }

    return "Prime";

} // static std::string primalityFA( ...

static constexpr const char* not_prime {"Not prime"};
static constexpr const char* prime {"Prime"};

// Test case 0
TEST(PrimalityTest, TestCase0) {
    EXPECT_EQ(not_prime, primalityFA(12));
    EXPECT_EQ(prime, primalityFA(5));
    EXPECT_EQ(prime, primalityFA(7));
}

// Test case 1
TEST(PrimalityTest, TestCase1) {
    EXPECT_EQ(prime, primalityFA(31));
    EXPECT_EQ(not_prime, primalityFA(33));
}

// Test case 5
TEST(PrimalityTest, TestCase5) {
    EXPECT_EQ(not_prime, primalityFA(1));
}

// Test case 9
TEST(PrimalityTest, TestCase9) {
    EXPECT_EQ(not_prime, primalityFA(1));
    EXPECT_EQ(not_prime, primalityFA(4));
    EXPECT_EQ(not_prime, primalityFA(9));
    EXPECT_EQ(not_prime, primalityFA(16));
    EXPECT_EQ(not_prime, primalityFA(25));

    EXPECT_EQ(not_prime, primalityFA(36));
    EXPECT_EQ(not_prime, primalityFA(49));
    EXPECT_EQ(not_prime, primalityFA(64));
    EXPECT_EQ(not_prime, primalityFA(81));
    EXPECT_EQ(not_prime, primalityFA(100));

    EXPECT_EQ(not_prime, primalityFA(121));
    EXPECT_EQ(not_prime, primalityFA(144));
    EXPECT_EQ(not_prime, primalityFA(169));
    EXPECT_EQ(not_prime, primalityFA(196));
    EXPECT_EQ(not_prime, primalityFA(225));

    EXPECT_EQ(not_prime, primalityFA(256));
    EXPECT_EQ(not_prime, primalityFA(289));
    EXPECT_EQ(not_prime, primalityFA(324));
    EXPECT_EQ(not_prime, primalityFA(361));
    EXPECT_EQ(not_prime, primalityFA(400));

    EXPECT_EQ(not_prime, primalityFA(441));
    EXPECT_EQ(not_prime, primalityFA(484));
    EXPECT_EQ(not_prime, primalityFA(529));
    EXPECT_EQ(not_prime, primalityFA(576));
    EXPECT_EQ(not_prime, primalityFA(625));

    EXPECT_EQ(not_prime, primalityFA(676));
    EXPECT_EQ(not_prime, primalityFA(729));
    EXPECT_EQ(not_prime, primalityFA(784));
    EXPECT_EQ(not_prime, primalityFA(841));
    EXPECT_EQ(prime, primalityFA(907));
}

// Test case 10
TEST(PrimalityTest, TestCase10) {
    EXPECT_EQ(prime, primalityFA(2));
    EXPECT_EQ(prime, primalityFA(7));
    EXPECT_EQ(not_prime, primalityFA(1982));
    EXPECT_EQ(not_prime, primalityFA(14582734));
    EXPECT_EQ(not_prime, primalityFA(9891));
}