#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief First attempt solution segfaults for Test cases 2-4 but passes others
//! @param[in] arr Vector of numbers
//! @return Maximum of the minimum(s) of every window size
static std::vector<long> riddleFirstAttempt(std::vector<long> arr)
{
    std::vector<std::vector<long>> dp(
        arr.size(), std::vector<long>(arr.size(), -1L));
    
    //! Initialize first row of dp
    dp.front() = arr;
    
    for (int row = 1; row < static_cast<int>(arr.size()); ++row)
    {
        for (int col = row; col < static_cast<int>(arr.size()); ++col)
        {
            dp[row][col] = std::min(dp[row - 1][col - 1], arr[col]);
        }
    }
    
    std::vector<long> max_mins {};
    max_mins.reserve(arr.size());
    
    for (const auto& row_vec : dp)
    {
        max_mins.emplace_back(
            *std::max_element(row_vec.cbegin(), row_vec.cend()));
    }
    return max_mins;

} // static std::vector<long> riddleFirstAttempt( ...

// Test case 6
TEST(RiddleTest, TestCase6) {
    const std::vector<long> input {2L, 6L, 1L, 12L};
    const std::vector<long> expected_output {12L, 2L, 1L, 1L};

    auto result = riddleFirstAttempt(input);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}

// Test case 7
TEST(RiddleTest, TestCase7) {
    const std::vector<long> input {1L, 2L, 3L, 5L, 1L, 13L, 3L};
    const std::vector<long> expected_output {13L, 3L, 2L, 1L, 1L, 1L, 1L};

    auto result = riddleFirstAttempt(input);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}

// Test case 8
TEST(RiddleTest, TestCase8) {
    const std::vector<long> input {3L, 5L, 4L, 7L, 6L, 2L};
    const std::vector<long> expected_output {7L, 6L, 4L, 4L, 3L, 2L};

    auto result = riddleFirstAttempt(input);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}