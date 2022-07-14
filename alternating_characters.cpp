#include <gtest/gtest.h>

#include <string>

static int alternatingCharacters(std::string s)
{
    // Minimum number of deletions
    int n_deletes {};
    
    // Char to compare characters in s to
    auto iter_char = s.front();
    
    for (auto it = s.cbegin() + 1; it != s.cend(); ++it)
    {
        if (iter_char == *it) {
            ++n_deletes;
        }
        else
        {
            iter_char = *it;
        }
    }
    
    return n_deletes;

} // static int alternatingCharacters( ...

// Test sample input given in problem description
TEST(AlternatingCharactersTest, SampleInput) {
    EXPECT_EQ(2, alternatingCharacters("AABAAB"));
}

// Test case 0
TEST(AlternatingCharactersTest, TestCase0) {
    EXPECT_EQ(3, alternatingCharacters("AAAA"));
    EXPECT_EQ(4, alternatingCharacters("BBBBB"));
    EXPECT_EQ(0, alternatingCharacters("ABABABAB"));
    EXPECT_EQ(0, alternatingCharacters("BABABA"));
    EXPECT_EQ(4, alternatingCharacters("AAABBB"));
}

// Test case 13
TEST(AlternatingCharactersTest, TestCase13) {
    EXPECT_EQ(6, alternatingCharacters("AAABBBAABB"));
    EXPECT_EQ(4, alternatingCharacters("AABBAABB"));
    EXPECT_EQ(1, alternatingCharacters("ABABABAA"));
}

// Test case 14
TEST(AlternatingCharactersTest, TestCase14) {
    EXPECT_EQ(3, alternatingCharacters("ABBABBAA"));
}