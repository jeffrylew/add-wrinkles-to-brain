#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <string>

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

// Test case 0
TEST(AbbreviationTest, TestCase0) {
    EXPECT_EQ("YES", abbreviationFirstAttempt("daBcd", "ABC"));
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
}

// Test case 15
TEST(AbbreviationTest, TestCase15) {
    EXPECT_EQ("NO", abbreviationFirstAttempt("AbCdE", "AFE"));
    EXPECT_EQ("NO", abbreviationFirstAttempt("beFgH", "EFG"));
    EXPECT_EQ("YES", abbreviationFirstAttempt("beFgH", "EFH"));
}