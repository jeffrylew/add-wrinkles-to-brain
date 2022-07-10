#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <string>

//! @brief Helper function to create map of chars and counts from string
//! @param[in] str Reference to string to create character/count map from
//! @return Map of characters in str and corresponding counts
static std::map<char, int> mapifyString(const std::string& str)
{
    // Map of characters and their counts in s1
    std::map<char, int> char_map {};
    
    std::for_each(str.cbegin(),
                  str.cend(),
                  [&](char c)
                  {
                      auto ret = char_map.emplace(c, 1);
                      if (not ret.second)
                      {
                          // Character already in map so increment count
                          ++ret.first->second;
                      }
                  });
                  
    return char_map;
    
} // std::map<char, int> mapifyString( ...

//! @brief Helper function determining if s2 is an anagram of s1
//! @param[in] s1 Reference to first string
//! @param[in] s2 Reference to second string
//! @return True is s2 is an anagram of s1, else false
static bool isAnagramTimedOut(const std::string& s1, const std::string& s2)
{
    //! @details This version timed out for Test case 4

    // Inputs must have same size and not be empty
    if (s1.empty() || s2.empty() || s1.size() != s2.size())
    {
        return false;
    }
    
    // Map of characters and their counts in s1
    auto s1_char_map = mapifyStringTimedOut(s1);
    
    // Iterate through characters in s2 and decrement counts in s1_char_map
    // If char from s2 is not in s1_char_map, s2 is not an anagram
    // If count for a char is 0, remove it from map
    // If map is empty after all chars in s2 are processed, is anagram
    for (const auto c : s2)
    {
        auto it = s1_char_map.find(c);
        if (it == s1_char_map.end())
        {
            // Char from s2 is not in s1_char_map
            // s2 is not an anagram
            return false;
        }
        
        // Decrement count and if it zero, remove char from map
        if (--it->second == 0)
        {
            s1_char_map.erase(it);
        }
        
    } // for (const auto c : s2)
    
    // s2 is an anagram of s1 if s1_char_map is empty
    return s1_char_map.empty();
    
} // bool isAnagramTimedOut( ...

static int sherlockAndAnagramsTimedOut(std::string s)
{
    //! @details This version timed out for Test case 4

    // Total number of anagrams
    int n_anagrams {};
    
    const auto s_size = s.size();
    
    // Generate all possible substrings with lengths up to s_size-1
    // Outer loop controls substring lengths for s1 and s2
    for (std::size_t len = 1; len < s_size; ++len)
    {
        // Substring positions for s1
        for (std::size_t pos1 = 0; pos1 + len < s_size; ++pos1)
        {
            auto s1 = s.substr(pos1, len);
            
            // Substring positions for s2
            for (std::size_t pos2 = pos1 + 1; pos2 + len <= s_size; ++pos2)
            {
                auto s2 = s.substr(pos2, len);
                
                if (isAnagramTimedOut(s1, s2)) {
                    ++n_anagrams;
                }
            }
        }
    }
    
    return n_anagrams;

} // static int sherlockAndAnagramsTimedOut( ...

// Try sample input given in problem description
TEST(SherlockAndAnagramsTest, SampleInput) {
    EXPECT_EQ(2, sherlockAndAnagramsTimedOut("mom"));
}

// Try Test case 0
TEST(SherlockAndAnagramsTest, TestCase0) {
    EXPECT_EQ(4, sherlockAndAnagramsTimedOut("abba"));
    EXPECT_EQ(0, sherlockAndAnagramsTimedOut("abcd"));
}

// Try Test case 1
TEST(SherlockAndAnagramsTest, TestCase1) {
    EXPECT_EQ(3, sherlockAndAnagramsTimedOut("ifailuhkqq"));
    EXPECT_EQ(10, sherlockAndAnagramsTimedOut("kkkk"));
}

// Try Test case 2
TEST(SherlockAndAnagramsTest, TestCase2) {
    EXPECT_EQ(5, sherlockAndAnagramsTimedOut("cdcd"));
}