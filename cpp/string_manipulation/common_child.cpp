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

// Test case 6
TEST(CommonChildTest, TestCase6) {
    EXPECT_EQ(2, commonChildFirstAttempt("HARRY", "SALLY"));
}

// Test case 7
TEST(CommonChildTest, TestCase7) {
    EXPECT_EQ(0, commonChildFirstAttempt("AA", "BB"));
}

// Test case 14
TEST(CommonChildTest, TestCase14) {
    EXPECT_EQ(3, commonChildFirstAttempt("SHINCHAN", "NOHARAAA"));
}