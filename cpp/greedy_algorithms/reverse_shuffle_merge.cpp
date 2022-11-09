#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>

//! @brief First attempt solution only passes Test cases 0, 11, 15, and 16
static std::string reverseShuffleMergeFA(std::string s)
{
    std::array<int, 26> letter_count {{}};
    
    //! Lower bound index for characters
    constexpr auto char_lb = static_cast<int>('a');
    
    //! Increment letter count based on lower case ascii letters
    for (const auto c : s)
    {
        ++letter_count[static_cast<int>(c) - char_lb];
    }
    
    //! Divide counts by two for letters in A
    std::transform(letter_count.begin(),
                   letter_count.end(),
                   letter_count.begin(),
                   [](int count) -> int { return count / 2; });
    
    //! Get lexicographically smallest letter with nonzero count
    auto first_letter_it = std::find_if(letter_count.cbegin(),
                                        letter_count.cend(),
                                        [](int count) -> bool {
                                            return count > 0;
                                        });

    const auto first_letter = static_cast<char>(
        first_letter_it - letter_count.begin() + char_lb);
    
    //! Search for last instance of latter letter in string
    std::string output {};
    for (auto it = s.crbegin(); it != s.crend(); ++it)
    {
        const auto char_idx = static_cast<int>(*it) - char_lb;
        if (output.empty())
        {
            if (*it != first_letter)
            {
                continue;
            }
            output += *it;
            --letter_count[char_idx];
        }
        else
        {
            if (0 == letter_count[char_idx])
            {
                //! Current character cannot be part of output string
                continue;
            }
            
            //! Add current character to output string
            output += *it;
            --letter_count[char_idx];
        }
    }
    
    return output;

} // static reverseShuffleMergeFA( ...

// Test case 0
TEST(TestReverseShuffleMerge, TestCase0) {
    EXPECT_EQ("egg", reverseShuffleMergeFA("eggegg"));
}

// Test case 15
TEST(TestReverseShuffleMerge, TestCase15) {
    EXPECT_EQ("agfedcb", reverseShuffleMergeFA("abcdefgabcdefg"));
}

// Test case 16
TEST(TestReverseShuffleMerge, TestCase16) {
    EXPECT_EQ("aeiou", reverseShuffleMergeFA("aeiouuoiea"));
}