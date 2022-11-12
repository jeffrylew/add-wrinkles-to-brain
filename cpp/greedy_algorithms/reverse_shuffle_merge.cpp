#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <stack>
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

} // static std::string reverseShuffleMergeFA( ...

//! @brief Solution from HR discussion section
static std::string reverseShuffleMergeDS1(std::string s)
{
    //! @details
    //!     https://www.hackerrank.com/challenges/reverse-shuffle-merge/forum

    std::array<int, 26> char_freq {{}};

    //! Lower bound index for characters
    constexpr auto char_lb = static_cast<int>('a');

    //! Increment char frequencies based on lower case ascii letters
    for (const auto c : s)
    {
        ++char_freq[static_cast<int>(c) - char_lb];
    }

    //! Copy char_freq array before dividing frequencies
    auto remain_chars = char_freq;

    //! Divide frequencies by two
    std::transform(char_freq.begin(),
                   char_freq.end(),
                   char_freq.begin(),
                   [](int freq) -> int { return freq / 2; });

    std::array<int, 26> used_chars {{}};
    std::stack<char>    res {};

    auto can_pop = [&](char c) -> bool {
        const auto c_idx        = static_cast<int>(c) - char_lb;
        const auto needed_chars = char_freq[c_idx];
        return used_chars[c_idx] + remain_chars[c_idx] - 1 >= needed_chars;
    };

    for (auto it = s.crbegin(); it != s.crend(); ++it)
    {
        const auto char_idx = static_cast<int>(*it) - char_lb;
        if (char_freq[char_idx] - used_chars[char_idx] > 0)
        {
            while (not res.empty() && (res.top() > *it) && can_pop(res.top()))
            {
                const auto removed_char = res.top();
                res.pop();
                
                const auto rchar_idx = static_cast<int>(removed_char) - char_lb;
                --used_chars[rchar_idx];
            }
            
            ++used_chars[char_idx];
            res.push(*it);
        }

        --remain_chars[char_idx];

    } // for (auto it = s.crbegin(); ...

    std::string output {};
    output.reserve(res.size());

    while (not res.empty())
    {
        output.insert(output.cbegin(), res.top());
        res.pop();
    }
    
    return output;

} // static std::string reverseShuffleMergeDS1( ...

// Test case 0
TEST(TestReverseShuffleMerge, TestCase0) {
    EXPECT_EQ("egg", reverseShuffleMergeFA("eggegg"));
    EXPECT_EQ("egg", reverseShuffleMergeDS1("eggegg"));
}

// Test case 15
TEST(TestReverseShuffleMerge, TestCase15) {
    EXPECT_EQ("agfedcb", reverseShuffleMergeFA("abcdefgabcdefg"));
    EXPECT_EQ("agfedcb", reverseShuffleMergeDS1("abcdefgabcdefg"));
}

// Test case 16
TEST(TestReverseShuffleMerge, TestCase16) {
    EXPECT_EQ("aeiou", reverseShuffleMergeFA("aeiouuoiea"));
    EXPECT_EQ("aeiou", reverseShuffleMergeDS1("aeiouuoiea"));
}