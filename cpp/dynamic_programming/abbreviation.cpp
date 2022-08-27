#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <locale>
#include <string>
#include <vector>

//! @brief First attempt solution fails Test cases 6-14
static std::string abbreviationFirstAttempt(std::string a, std::string b)
{
    if (a.size() < b.size())
    {
        //! Insufficient characters in a to form b
        return "NO";
    }
    
    //! Iterator to char in a
    auto it_a = a.cbegin();
    
    //! Iterator to char in b
    auto it_b = b.cbegin();
    
    while (it_b != b.cend())
    {
        const auto b_char = *it_b;
        
        //! Flag indicating char in b is uppercase
        bool is_uppercase {b_char >= 65 && b_char <= 90};
        
        //! Must find exact lowercase match in a
        //! but if is_uppercase is true then char
        //! in a can also be uppercase
        while (it_a != a.cend())
        {
            //! @todo Need to handle repeated lowercase chars and adjacent
            //!       lowercase and uppercase chars of same letter
            if (*it_a == b_char || (is_uppercase && *it_a == b_char + 32))
            {
                //! Found matching character in a
                //! Process next character in b
                ++it_a;
                break;
            }
            else if (*it_a >= 65 && *it_a <= 90)
            {
                //! Character in a is not matching and
                //! is uppercase. It cannot be removed
                return "NO";
            }
            
            //! Character in a is not matching but
            //! is lowercase so it can be removed
            ++it_a;
        }
        
        if (*std::prev(it_a) == b_char
            || (is_uppercase && *std::prev(it_a) == b_char + 32))
        {
            ++it_b;   
        }
        
        if (it_b != b.cend() && it_a == a.cend())
        {
            return "NO";
        }
        
    } // while (it_b != b.cend())
    
    //! All remaining chars in a must be lowercase for a to match b
    if (std::all_of(it_a,
                    a.cend(),
                    [](char c) -> bool {
                        return c >= 97 && c <= 122;
                    }))
    {
        return "YES";
    }
    
    return "NO";

} // static std::string abbreviationFirstAttempt( ...

//! @brief Solution from discussion section
//! @param[in] a String to modify
//! @param[in] b String to match
//! @return "YES" if a can be modified to match b, else "NO"
static std::string abbreviationDiscussionSolution1(std::string a, std::string b)
{
    //! @details https://www.hackerrank.com/challenges/abbr/forum

    //! Addition of 1ULL accounts for empty substrings
    const auto dp_len_a = a.size() + 1ULL;
    const auto dp_len_b = b.size() + 1ULL;
    
    //! dp tracks whether the substring of b is a
    //! subsequence of substring of a. Values are
    //! initialized to false
    //!
    //! dp_len_a rows, assume this is y-axis
    //! dp_len_b cols, assume this is x-axis
    std::vector<std::vector<bool>> dp(
        dp_len_b, std::vector<bool>(dp_len_a, false));
    
    //! Initialize case when string a (to modify)
    //! and string b (to match) are both empty
    dp[0][0] = true;
    
    //! Index col = 0 represents empty b substring
    //! Index row = 0 represents empty a substring
    
    //! Use classic C++ locale
    const std::locale loc {};

    for (std::size_t col = 0; col < dp_len_b; ++col)
    {
        //! This loop could start with row = 1 and checks
        //! on (row > 0) could be removed below
        for (std::size_t row = 0; row < dp_len_a; ++row)
        {
            //! Case when letters remain in string b (to match) but
            //! there are no letters left in string a (to modify):
            //! col > 0 and row == 0 already initialized to false
            
            if (col == 0 && row > 0)
            {
                //! Current character in a
                const auto char_a = a[row - 1];
                
                //! Substring of b (to match) is empty but
                //! there are chars left in a (to modify)
                //! Current char in a needs to be lowercase AND
                //! prior substring of a is an abbreviation
                dp[col][row] = std::islower(char_a, loc) && dp[col][row - 1];
            }
            else if (col > 0 && row > 0)
            {
                //! Case when substrings of a and b are not empty
                
                const auto char_a = a[row - 1];
                const auto char_b = b[col - 1];
                
                if (char_a == char_b)
                {
                    //! Char in a exactly matches char in b
                    //! (both lowercase or both uppercase)
                    //! Current substring b is a subsequence
                    //! of substring a if the prior substrings
                    //! were abbreviations
                    dp[col][row] = dp[col - 1][row - 1];
                }
                else if (std::toupper(char_a, loc) == char_b)
                {
                    //! Char in a is lowercase version of char in b
                    //! Check if prior substrings were abbreviations
                    //! or if substring b is still an abbreviation of
                    //! substring a if this lowercase char is dropped
                    dp[col][row] = dp[col - 1][row - 1] || dp[col][row - 1];
                }
                else if (not (
                    std::isupper(char_a, loc) && std::isupper(char_b, loc)))
                {
                    //! The first line below should result in false:
                    //!
                    //! (Char in a uppercase, char in b lowercase) OR
                    //! (char in a lowercase, char in b uppercase BUT
                    //! char in a not same letter as char in b) OR
                    //! (char in a lowercase, char in b lowercase BUT
                    //! char in a not same letter as char in b)
                    
                    dp[col][row] = dp[col][row - 1];
                }
                
                //! Char in a uppercase, char in b uppercase but they
                //! aren't the same letter - defaults to false
                
            } // else if (col > 0 && row > 0)
            
        } // for (std::size_t row = 0; ...
        
    } // for (std::size_t col = 0; ...
    
    return dp[b.size()][a.size()] ? "YES" : "NO";

} // static std::string abbreviationDiscussionSolution1( ...

// Test case 0
TEST(AbbreviationTest, TestCase0) {
    EXPECT_EQ("YES", abbreviationFirstAttempt("daBcd", "ABC"));

    EXPECT_EQ("YES", abbreviationDiscussionSolution1("daBcd", "ABC"));
}

// Test case 1
TEST(AbbreviationTest, TestCase1) {
    EXPECT_EQ("YES", abbreviationFirstAttempt("Pi", "P"));
    EXPECT_EQ("NO", abbreviationFirstAttempt("AfPZN", "APZNC"));
    EXPECT_EQ("NO", abbreviationFirstAttempt("LDJAN", "LJJM"));
    EXPECT_EQ("YES", abbreviationFirstAttempt("UMKFW", "UMKFW"));
    EXPECT_EQ("NO", abbreviationFirstAttempt("KXzQ", "K"));
    EXPECT_EQ("YES", abbreviationFirstAttempt("LIT", "LIT"));
    EXPECT_EQ("YES", abbreviationFirstAttempt("QYCH", "QYCH"));
    EXPECT_EQ("YES", abbreviationFirstAttempt("DFIQG", "DFIQG"));
    EXPECT_EQ("NO", abbreviationFirstAttempt("sYOCa", "YOCN"));
    EXPECT_EQ("NO", abbreviationFirstAttempt("JHMWY", "HUVPW"));

    EXPECT_EQ("YES", abbreviationDiscussionSolution1("Pi", "P"));
    EXPECT_EQ("NO", abbreviationDiscussionSolution1("AfPZN", "APZNC"));
    EXPECT_EQ("NO", abbreviationDiscussionSolution1("LDJAN", "LJJM"));
    EXPECT_EQ("YES", abbreviationDiscussionSolution1("UMKFW", "UMKFW"));
    EXPECT_EQ("NO", abbreviationDiscussionSolution1("KXzQ", "K"));
    EXPECT_EQ("YES", abbreviationDiscussionSolution1("LIT", "LIT"));
    EXPECT_EQ("YES", abbreviationDiscussionSolution1("QYCH", "QYCH"));
    EXPECT_EQ("YES", abbreviationDiscussionSolution1("DFIQG", "DFIQG"));
    EXPECT_EQ("NO", abbreviationDiscussionSolution1("sYOCa", "YOCN"));
    EXPECT_EQ("NO", abbreviationDiscussionSolution1("JHMWY", "HUVPW"));
}

// Test case 15
TEST(AbbreviationTest, TestCase15) {
    EXPECT_EQ("NO", abbreviationFirstAttempt("AbCdE", "AFE"));
    EXPECT_EQ("NO", abbreviationFirstAttempt("beFgH", "EFG"));
    EXPECT_EQ("YES", abbreviationFirstAttempt("beFgH", "EFH"));

    EXPECT_EQ("NO", abbreviationDiscussionSolution1("AbCdE", "AFE"));
    EXPECT_EQ("NO", abbreviationDiscussionSolution1("beFgH", "EFG"));
    EXPECT_EQ("YES", abbreviationDiscussionSolution1("beFgH", "EFH"));
}