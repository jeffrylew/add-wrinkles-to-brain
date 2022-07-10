#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <map>
#include <stdexcept>
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
    auto s1_char_map = mapifyString(s1);
    
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

//! @brief Helper function determining if s2 is an anagram of s1
//! @param[in] s1_char_map Map of characters in s1 and their counts by value
//! @param[in] s2          Reference to second string
//! @return True is s2 is an anagram of s1, else false
static bool isAnagram(std::map<char, int> s1_char_map, const std::string& s2)
{
    /*
     * Usage in sherlockAndAnagrams ensures these preconditions are true
     *
    // Inputs must have same size and not be empty
    if (s1.empty() || s2.empty() || s1.size() != s2.size())
    {
        return false;
    }
    */
    
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
    
} // bool isAnagram( ...

//! @brief Anagram helper function, compiled from discussions section
//! @param[in] s1 Reference to first string
//! @param[in] s2 Reference to second string
//! @pre s1 and s2 have the same size
//! @return True is s2 is an anagram of s1, else false
static bool isAnagramDiscussionSolution(
    const std::string& s1,
    const std::string& s2)
{
    // Number of lowercase letters in ascii [a-z]
    static constexpr std::size_t n_lowercase_letters {26};

    // Array containing counts of characters in s1 and s2
    // Precondition is s1 and s2 have the same size
    // For each char in s1, increment the count at the corresponding index
    // ('a' = ascii 97 is at index 0 and all other indices are relative to it).
    // For each char in s2, decrement the count at the corresponding index
    std::array<int, n_lowercase_letters> char_count_arr {{}};
    for (std::size_t i = 0; i < s1.size(); ++i)
    {
        try
        {
            // Uses ascii value of 97 for 'a'
            ++char_count_arr.at(static_cast<std::size_t>(s1.at(i) - 'a'));
            --char_count_arr.at(static_cast<std::size_t>(s2.at(i) - 'a'));
        }
        catch (const std::out_of_range& /* ex */)
        {
            // Either s1.size() != s2.size() or there are non-lowercase letters
            return false;
        }
    }
    
    // If all entries in char_count_arr are 0, s2 is an anagram of s1
    return std::all_of(char_count_arr.cbegin(),
                       char_count_arr.cend(),
                       [](decltype(char_count_arr)::value_type count) -> bool
                       {
                           return count == 0;
                       });

} // static bool isAnagramDiscussionSolution( ...

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
                
                if (isAnagramTimedOut(s1, s2))
                {
                    ++n_anagrams;
                }
            }
        }
    }
    
    return n_anagrams;

} // static int sherlockAndAnagramsTimedOut( ...

static int sherlockAndAnagrams(std::string s)
{
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

            // Create map of characters and their counts for s1
            auto s1_char_map = mapifyString(s1);
            
            // Substring positions for s2
            for (std::size_t pos2 = pos1 + 1; pos2 + len <= s_size; ++pos2)
            {
                auto s2 = s.substr(pos2, len);
                
                if (isAnagram(s1_char_map, s2))
                {
                    ++n_anagrams;
                }
            }
        }
    }
    
    return n_anagrams;

} // static int sherlockAndAnagrams( ...

static int sherlockAndAnagramsDiscussionSolution(std::string s)
{
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
                
                if (isAnagramDiscussionSolution(s1, s2))
                {
                    ++n_anagrams;
                }
            }
        }
    }
    
    return n_anagrams;

} // static int sherlockAndAnagramsDiscussionSolution( ...

// Try sample input given in problem description
TEST(SherlockAndAnagramsTest, SampleInput) {
    EXPECT_EQ(2, sherlockAndAnagramsTimedOut("mom"));

    EXPECT_EQ(2, sherlockAndAnagrams("mom"));

    EXPECT_EQ(2, sherlockAndAnagramsDiscussionSolution("mom"));
}

// Try Test case 0
TEST(SherlockAndAnagramsTest, TestCase0) {
    EXPECT_EQ(4, sherlockAndAnagramsTimedOut("abba"));
    EXPECT_EQ(0, sherlockAndAnagramsTimedOut("abcd"));

    EXPECT_EQ(4, sherlockAndAnagrams("abba"));
    EXPECT_EQ(0, sherlockAndAnagrams("abcd"));

    EXPECT_EQ(4, sherlockAndAnagramsDiscussionSolution("abba"));
    EXPECT_EQ(0, sherlockAndAnagramsDiscussionSolution("abcd"));
}

// Try Test case 1
TEST(SherlockAndAnagramsTest, TestCase1) {
    EXPECT_EQ(3, sherlockAndAnagramsTimedOut("ifailuhkqq"));
    EXPECT_EQ(10, sherlockAndAnagramsTimedOut("kkkk"));

    EXPECT_EQ(3, sherlockAndAnagrams("ifailuhkqq"));
    EXPECT_EQ(10, sherlockAndAnagrams("kkkk"));

    EXPECT_EQ(3, sherlockAndAnagramsDiscussionSolution("ifailuhkqq"));
    EXPECT_EQ(10, sherlockAndAnagramsDiscussionSolution("kkkk"));
}

// Try Test case 2
TEST(SherlockAndAnagramsTest, TestCase2) {
    EXPECT_EQ(5, sherlockAndAnagramsTimedOut("cdcd"));

    EXPECT_EQ(5, sherlockAndAnagrams("cdcd"));

    EXPECT_EQ(5, sherlockAndAnagramsDiscussionSolution("cdcd"));
}