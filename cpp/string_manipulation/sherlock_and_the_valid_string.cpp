#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <numeric>
#include <string>

//! @brief Get index in array corresponding to c
//! @param[in] c Lowercase char with ascii value in [97, 122]
//! @pre c is a lowercase character
//! @return Index of c in array representing lowercase characters
static std::size_t getIdx(char c)
{
    return static_cast<std::size_t>(static_cast<int>(c) - 97);
}

//! @brief First attempt solution fails Test cases 4, 7, 13, and 16
static std::string isValidFirstAttempt(std::string s)
{
    // Array of lowercase character counts
    // ascii characters a to z map to indices 0 to 25
    std::array<int, 26ULL> char_counts {{}};
    
    // Populate char_counts with character counts in s
    for (const auto c : s)
    {
        ++char_counts.at(getIdx(c));
    }
    
    // Get iterator to first non-zero count
    auto first_non_zero_it = std::find_if(char_counts.cbegin(),
                                          char_counts.cend(),
                                          [](int count) -> bool {
                                              return count != 0;
                                          });

    // Get iterator to minimum count that is non-zero
    auto min_it = std::min_element(first_non_zero_it,
                                   char_counts.cend(),
                                   [](int lhs, int rhs) -> bool {
                                       return lhs != 0 && lhs < rhs;
                                   });
    
    if (min_it == char_counts.cend())
    {
        // This should never happen since input s cannot be empty
        return "NO";
    }
    else
    {
        // Normalize non-zero values in char_counts by minimum count
        const auto non_zero_min = *min_it;
        std::transform(char_counts.begin(),
                       char_counts.end(),
                       char_counts.begin(),
                       [=](int count) -> int {
                           return (count == 0) ? 0 : count - non_zero_min;
                       });
                       
        // If sum of elements in char_counts is more than 1 then invalid
        return (std::accumulate(char_counts.cbegin(),
                                char_counts.cend(),
                                0) < 2) ? "YES" : "NO";
    }

} // static std::string isValidFirstAttempt( ...

// Test case 0
TEST(IsValidTest, TestCase0) {
    EXPECT_EQ("NO", isValidFirstAttempt("aabbcd"));
}

// Test case 1
TEST(IsValidTest, TestCase1) {
    EXPECT_EQ("NO", isValidFirstAttempt("aabbccddeefghi"));
}

// Test case 4, first solution failed this along with Test cases 7, 13, and 16
TEST(IsValidTest, TestCase4) {
    EXPECT_NE("YES", isValidFirstAttempt("aabbc"));
}

// Test case 18
TEST(IsValidTest, TestCase18) {
    EXPECT_EQ("YES", isValidFirstAttempt("abcdefghhgfedecba"));
}