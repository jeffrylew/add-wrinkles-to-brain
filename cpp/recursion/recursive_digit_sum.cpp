#include <gtest/gtest.h>

#include <string>

//! @brief Helper function for first attempt solution that sums digits in string
//! @param[in] n Reference to std::string containing number with digits to sum
//! @param[in] k Number of times to concatenate n
//! @return Sum of digits from string n repeated k times
static int sum_digits(const std::string& n, int k)
{
    int sum {};

    //! ASCII value of '0'
    static constexpr auto zero_char = static_cast<int>('0');

    //! Add digits in string n
    for (const auto c : n)
    {
        sum += static_cast<int>(c) - zero_char;
    }

    //! Sum of digits is repeated k times
    return sum * k;

} // static int sum_digits( ...

//! @brief First attempt solution to determine super digit fails test cases 7, 8
//! @param[in] n Reference to std::string containing number with digits to sum
//! @param[in] k Number of times to concatenate n
//! @return Super digit of n repeated k times
static int superDigitFA(std::string n, int k)
{
    const auto n_size = static_cast<int>(n.size());

    if (1 == n_size)
    {
        return sum_digits(n, 1);
    }

    const auto sum_digits_str = std::to_string(sum_digits(n, k));

    return superDigitFA(sum_digits_str, 1);

} // static int superDigitFA( ...

// Test case 0
TEST(SuperDigitTest, TestCase0) {
    EXPECT_EQ(3, superDigitFA("148", 3));
}

// Test case 10
TEST(SuperDigitTest, TestCase10) {
    EXPECT_EQ(8, superDigitFA("9875", 4));
}

// Test case 11
TEST(SuperDigitTest, TestCase11) {
    EXPECT_EQ(9, superDigitFA("123", 3));
}