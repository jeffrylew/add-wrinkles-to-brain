#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cmath>
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

static int makeAnagram(std::string a, std::string b)
{
    // Array of lowercase character counts
    // ascii characters a to z map to indices 0 to 25
    std::array<int, 26ULL> char_counts {{}};
    
    // Populate char_counts with character counts in a
    for (const auto c : a)
    {
        ++char_counts.at(getIdx(c));
    }
    
    // Decrement char_counts with character counts in b
    for (const auto c : b)
    {
        --char_counts.at(getIdx(c));
    }
    
    return std::accumulate(char_counts.cbegin(),
                           char_counts.cend(),
                           0,
                           [](int lhs, int rhs) -> int {
                               return static_cast<int>(
                                   std::abs(lhs) + std::abs(rhs));
                           });

} // static int makeAnagram( ...

// Test case 0
TEST(MakeAnagramTest, TestCase0) {
    EXPECT_EQ(4, makeAnagram("cde", "abc"));
}

// Test case 1
TEST(MakeAnagramTest, TestCase1) {
    EXPECT_EQ(30, makeAnagram("fcrxzwscanmligyxyvym",
                              "jxwtrhvujlmrpdoqbisbwhmgpmeoke"));
}

// Test case 15
TEST(MakeAnagramTest, TestCase15) {
    EXPECT_EQ(2, makeAnagram("showman", "woman"));
}