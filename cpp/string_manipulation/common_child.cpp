#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

//! @brief First attempt solution passes Test cases 6-8, 14
//! @param[in] s1 First string
//! @param[in] s2 Second string
//! @return Length of longest string which is a common child of input strings
static int commonChildFirstAttempt(std::string s1, std::string s2)
{
    //! @details Time complexity O(s1.size() * s2.size())
    //!          Space complexity O(s1.size() * s2.size())

    //! Define sizes for dp matrix, add 1 to account for empty strings
    //! rows = y-axis, cols = x-axis
    const auto dp_nrows = 1ULL + s1.size();
    const auto dp_ncols = 1ULL + s2.size();
    
    //! dp stores max length of common child strings, initialized to 0
    std::vector<std::vector<int>> dp(dp_ncols, std::vector<int>(dp_nrows, 0));
    
    for (std::size_t col = 1; col < dp_ncols; ++col)
    {
        for (std::size_t row = 1; row < dp_nrows; ++row)
        {
            //! Current chars in s1 and s2
            const auto s1_char = s1[row - 1];
            const auto s2_char = s2[col - 1];
            
            if (s1_char == s2_char)
            {
                //! Just needed dp[col - 1][row - 1] instead of dp[col][row - 1]
                //! See en.wikipedia.org/wiki/Longest_common_subsequence_problem
                dp[col][row] = dp[col - 1][row - 1] + 1;
            }
            else
            {
                dp[col][row] = std::max(dp[col][row - 1], dp[col - 1][row]);
            }
        }
    }
    
    return dp[s2.size()][s1.size()];

} // static int commonChildFirstAttempt( ...

//! @brief Optimization by reducing the problem set
//! @param[in] s1 First string
//! @param[in] s2 Second string
//! @return Length of longest string which is a common child of input strings
static int commonChildOptimized(std::string s1, std::string s2)
{
    //! @details In most real-world cases, beginnings and ends of files change.
    //!          If only a few items have changed in the middle, the beginning
    //!          and end can be eliminated. This reduces the memory requirements
    //!          for the matrix and the number of comparisons that must be done.
    //!
    //! See https://en.wikipedia.org/wiki/Longest_common_subsequence_problem

    int  start_idx {0};
    auto s1_end_idx = static_cast<int>(s1.size() - 1);
    auto s2_end_idx = static_cast<int>(s2.size() - 1);

    //! Trim off matching characters at beginning
    while (start_idx <= s1_end_idx    //
           && start_idx <= s2_end_idx //
           && s1[start_idx] == s2[start_idx])
    {
        ++start_idx;
    }
    
    //! Trim off matching characters at end
    while (start_idx <= s1_end_idx    //
           && start_idx <= s2_end_idx //
           && s1[s1_end_idx] == s2[s2_end_idx])
    {
        --s1_end_idx;
        --s2_end_idx;
    }
    
    //! Define sizes for dp matrix, add 2 to account for empty strings
    std::vector<std::vector<int>> dp(
        s2_end_idx - start_idx + 2,
        std::vector<int>(s1_end_idx - start_idx + 2, 0));
    
    for (int i = start_idx; i <= s1_end_idx; ++i)
    {
        for (int j = start_idx; j <= s2_end_idx; ++j)
        {
            //! Current chars in s1 and s2
            const auto s1_char = s1[i];
            const auto s2_char = s2[j];

            //! Indices into dp
            const auto dp_i = i - start_idx + 1;
            const auto dp_j = j - start_idx + 1;

            if (s1_char == s2_char)
            {
                dp[dp_i][dp_j] = dp[dp_i - 1][dp_j - 1] + 1;
            }
            else
            {
                dp[dp_i][dp_j] = std::max(dp[dp_i][dp_j - 1],
                                          dp[dp_i - 1][dp_j]);
            }
        }
    }
    
    return start_idx
        + dp[s2_end_idx - start_idx + 1][s1_end_idx - start_idx + 1]
        + (static_cast<int>(s1.size()) - s1_end_idx - 1);

} // static int commonChildOptimized( ...

// Test case 6
TEST(CommonChildTest, TestCase6) {
    EXPECT_EQ(2, commonChildFirstAttempt("HARRY", "SALLY"));
    EXPECT_EQ(2, commonChildOptimized("HARRY", "SALLY"));
}

// Test case 7
TEST(CommonChildTest, TestCase7) {
    EXPECT_EQ(0, commonChildFirstAttempt("AA", "BB"));
    EXPECT_EQ(0, commonChildOptimized("AA", "BB"));
}

// Test case 14
TEST(CommonChildTest, TestCase14) {
    EXPECT_EQ(3, commonChildFirstAttempt("SHINCHAN", "NOHARAAA"));
    EXPECT_EQ(3, commonChildOptimized("SHINCHAN", "NOHARAAA"));
}