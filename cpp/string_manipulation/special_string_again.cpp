#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>
#include <vector>

//! @brief Get index in array corresponding to c
//! @param[in] c Lowercase char with ascii value in [97, 122]
//! @pre c is a lowercase character
//! @return Index of c in array representing lowercase characters
static std::size_t getIdx(char c)
{
    return static_cast<std::size_t>(static_cast<int>(c) - 97);
}

//! @brief Get number of special substrings from vector of indices
//! @param[in] idx_per_char Reference to vector of indices for a character
//! @return Number of special substrings as a long
static long numSpecialSubstrings(const std::vector<int>& idx_per_char)
{
    //! @details Very crappy code. Triple nested for loops, yikes...
    //!          First attempt solution passes Test cases 0, 1, and 16
    //!          but times out for Test cases 2-15

    // Total number of special substrings per character
    long n_special_substr {};
    
    // Loop over all indices
    for (auto it = idx_per_char.cbegin(); it != idx_per_char.cend(); ++it)
    {
        // Loop over all substring sizes starting from 2 characters
        for (std::size_t substr_size = 2ULL;
             substr_size <= idx_per_char.size();
             ++substr_size)
        {
            if ((it - idx_per_char.cbegin()) + substr_size
                > idx_per_char.size())
            {
                // Substring at iter_idx is too large
                break;
            }
            
            // Vector to hold substring indices
            std::vector<int> substr_idx_vec(substr_size);
            std::copy_n(it, substr_size, substr_idx_vec.begin());
            
            // In vector of substring indices, check if adjacent indices only
            // differ by 1. The middle index can differ by 2 at most from the
            // previous if substr_size is even
            
            bool is_special_substr {true};
            for (std::size_t i = 1ULL; i < substr_size; ++i)
            {
                const auto idx_diff =
                    substr_idx_vec.at(i) - substr_idx_vec.at(i - 1ULL);
                
                if (0 == substr_size % 2 && i == substr_size / 2)
                {
                    // Check for the middle indices in substr_idx_vec
                    is_special_substr = is_special_substr && (idx_diff < 3);
                }
                else
                {
                    is_special_substr = is_special_substr && (idx_diff == 1);
                }
                
                if (not is_special_substr)
                {
                    break;
                }

            } // for (std::size_t i = 1ULL; ...
            
            if (is_special_substr)
            {
                ++n_special_substr;
            }
            
        } // for (std::size_t substr_size = 2ULL; ...
        
    } // for (auto it = idx_per_char.cbegin(); ...
    
    return n_special_substr;
    
} // static long numSpecialSubstrings( ...

static long substrCountFirstAttempt(int n, std::string s)
{
    //! @details Passes Test cases 0, 1, 16 but times out for Test cases 2-15

    // Total number of special substrings
    // Initialize to length of s since each character is a special substring
    long n_special_substr {n};

    // Number of lowercase letters in ascii [a-z]
    constexpr std::size_t n_lowercase_letters {26};
    
    // Array containing vectors of indices (ints) at which each char is present
    std::array<std::vector<int>, n_lowercase_letters> char_idx_arr {{}};
    
    for (std::size_t i = 0; i < static_cast<std::size_t>(n); ++i)
    {
        char_idx_arr.at(getIdx(s.at(i))).emplace_back(static_cast<int>(i));
    }
    
    for (const auto& idx_vec : char_idx_arr)
    {
        n_special_substr += numSpecialSubstrings(idx_vec);
    }

    return n_special_substr;

} // static long substrCountFirstAttempt( ...

//! @brief Solution from discussion section
static long substrCountDiscussionSolution(int n, std::string s)
{
    // Total number of special substrings
    long n_special_substr {};

    // Keep count of character repetitions in string while maintaining order
    std::vector<std::pair<char, int>> char_counts {};

    // Count per character in string (> 1 if character has repeated sequence)
    int count_per_char {};

    // Current character, initialized to null character
    char curr_char {'\0'};

    // 1st pass builds vector of characters and their counts
    for (const auto c : s)
    {
        if (c == curr_char)
        {
            ++count_per_char;
        }
        else
        {
            if (curr_char != '\0')
            {
                char_counts.emplace_back(curr_char, count_per_char);
            }
            curr_char      = c;
            count_per_char = 1;
        }

    } // for (const auto c : s)

    char_counts.emplace_back(curr_char, count_per_char);

    // 2nd pass accounts for substring combinations where all letters are same
    // For a string with n repeated chars, can make n*(n + 1)/2 substrings
    for (const auto& char_count : char_counts)
    {
        n_special_substr += (char_count.second * (char_count.second + 1)) / 2;
    }
    
    // 3rd pass accounts for substrings where all chars are same except middle
    for (std::size_t i = 1ULL; i < char_counts.size() - 1ULL; ++i)
    {
        const auto lhs_char  = char_counts.at(i - 1ULL).first;
        const auto rhs_char  = char_counts.at(i + 1ULL).first;
        const auto lhs_count = char_counts.at(i - 1ULL).second;
        const auto rhs_count = char_counts.at(i + 1ULL).second;
        const auto mid_count = char_counts.at(i).second;

        if (lhs_char == rhs_char && mid_count == 1)
        {
            n_special_substr += std::min(lhs_count, rhs_count);
        }
    }
    
    return n_special_substr;

} // static long substrCountDiscussionSolution( ...

// Test sample input given in problem description
TEST(SubstrCountTest, SampleInput) {
    EXPECT_EQ(12L, substrCountFirstAttempt(8, "mnonopoo"));

    EXPECT_EQ(12L, substrCountDiscussionSolution(8, "mnonopoo"));
}

// Test case 0
TEST(SubstrCountTest, TestCase0) {
    EXPECT_EQ(7L, substrCountFirstAttempt(5, "asasd"));

    EXPECT_EQ(7L, substrCountDiscussionSolution(5, "asasd"));
}

// Test case 1
TEST(SubstrCountTest, TestCase1) {
    EXPECT_EQ(10L, substrCountFirstAttempt(7, "abcbaba"));

    EXPECT_EQ(10L, substrCountDiscussionSolution(7, "abcbaba"));
}

// Test case 16
TEST(SubstrCountTest, TestCase16) {
    EXPECT_EQ(10L, substrCountFirstAttempt(4, "aaaa"));

    EXPECT_EQ(10L, substrCountDiscussionSolution(4, "aaaa"));
}