#include <gtest/gtest.h>

#include <cstdint>
#include <string>

//! @brief Helper function for first attempt solution that sums digits in string
//! @param[in] n Reference to std::string containing number with digits to sum
//! @param[in] k Number of times to concatenate n
//! @return Sum of digits from string n repeated k times
static std::int64_t sum_digits(const std::string& n, int k)
{
    std::int64_t sum {};

    //! ASCII value of '0'
    static constexpr auto zero_char = static_cast<std::int64_t>('0');

    //! Add digits in string n
    for (const auto c : n)
    {
        sum += static_cast<std::int64_t>(c) - zero_char;
    }

    //! Sum of digits is repeated k times
    return sum * static_cast<std::int64_t>(k);

} // static std::int64_t sum_digits( ...

//! @brief First attempt solution to determine super digit
//! @param[in] n Reference to std::string containing number with digits to sum
//! @param[in] k Number of times to concatenate n
//! @return Super digit of n repeated k times
static int superDigitFA(std::string n, int k)
{
    const auto n_size = static_cast<int>(n.size());

    if (1 == n_size)
    {
        return static_cast<int>(sum_digits(n, 1));
    }

    const auto sum_digits_str = std::to_string(sum_digits(n, k));

    return superDigitFA(sum_digits_str, 1);

} // static int superDigitFA( ...

//! @brief Solution from HR discussion section
//! @param[in] n Reference to std::string containing number with digits to sum
//! @param[in] k Number of times to concatenate n
//! @return Super digit of n repeated k times
static int superDigitDS1(std::string n, int k)
{
    //! @details https://www.hackerrank.com/challenges/recursive-digit-sum/forum

    const auto n_int = std::stoi(n);
    const auto x     = n_int * k % 9;

    return (0 == x) ? 9 : x;

} // static int superDigitDS1( ...

//! @brief Another solution from HR discussion section
//! @param[in] n Reference to std::string containing number with digits to sum
//! @param[in] k Number of times to concatenate n
//! @return Super digit of n repeated k times
static int superDigitDS2(std::string n, int k)
{
    //! @details https://www.hackerrank.com/challenges/recursive-digit-sum/forum

    if (1ULL == n.size())
    {
        return std::stoi(n);
    }
    
    std::int64_t sum {};
    for (const auto c : n)
    {
        sum += static_cast<std::int64_t>(c - '0');
    }

    return superDigitDS2(std::to_string(sum * static_cast<std::int64_t>(k)), 1);

} // static int superDigitDS2( ...

// Test case 0
TEST(SuperDigitTest, TestCase0) {
    EXPECT_EQ(3, superDigitFA("148", 3));
    EXPECT_EQ(3, superDigitDS1("148", 3));
    EXPECT_EQ(3, superDigitDS2("148", 3));
}

// Test case 10
TEST(SuperDigitTest, TestCase10) {
    EXPECT_EQ(8, superDigitFA("9875", 4));
    EXPECT_EQ(8, superDigitDS1("9875", 4));
    EXPECT_EQ(8, superDigitDS2("9875", 4));
}

// Test case 11
TEST(SuperDigitTest, TestCase11) {
    EXPECT_EQ(9, superDigitFA("123", 3));
    EXPECT_EQ(9, superDigitDS1("123", 3));
    EXPECT_EQ(9, superDigitDS2("123", 3));
}