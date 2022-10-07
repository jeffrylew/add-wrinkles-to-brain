#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
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

//! @brief Second attempt solution still segfaults for Test cases 2-4
//! @param[in] arr Vector of numbers
//! @return Maximum of the minimum(s) of every window size
static std::vector<long> riddleSecondAttempt(std::vector<long> arr)
{
    std::vector<std::vector<long>> dp(
        arr.size(), std::vector<long>(arr.size(), -1L));
    
    //! Initialize first row of dp
    dp.front() = arr;

    //! Output vector of maximum values
    //! Initialize with max value from arr
    std::vector<long> max_mins {};
    max_mins.reserve(arr.size());
    max_mins.emplace_back(*std::max_element(arr.cbegin(), arr.cend()));

    //! Keep track of max value in each row
    long row_max {-1L};
    
    for (int row = 1; row < static_cast<int>(arr.size()); ++row)
    {
        row_max = -1L;

        for (int col = row; col < static_cast<int>(arr.size()); ++col)
        {
            dp[row][col] = std::min(dp[row - 1][col - 1], arr[col]);

            if (dp[row][col] > row_max)
            {
                row_max = dp[row][col];
            }
        }

        //! Add row maximum to output vector
        max_mins.emplace_back(row_max);
    }

    return max_mins;

} // static std::vector<long> riddleSecondAttempt( ...

//! @brief Solution from HR discussion section
//! @param[in] arr Vector of numbers
//! @return Maximum of the minimum(s) of every window size
static std::vector<long> riddleDS(std::vector<long> arr)
{
    //! @details https://www.hackerrank.com/challenges/min-max-riddle/forum

    arr.push_back(-1L);

    int arr_size {static_cast<int>(arr.size())};
    int idx {};

    //! Output vector of maximum values
    std::vector<long> max_mins(arr.size() - 1ULL);

    std::stack<long> st {};

    while (idx < arr_size)
    {
        if (st.empty() || arr[idx] > arr[st.top()])
        {
            st.push(idx++);
        }
        else
        {
            auto val = arr[st.top()];
            st.pop();

            int len = st.empty() ? idx : idx - st.top() - 1;

            max_mins[len - 1] = std::max(val, max_mins[len - 1]);
        }

    } //while (idx < arr_size)

    for (int i =  arr_size - 3; i >= 0; --i)
    {
        max_mins[i] = std::max(max_mins[i], max_mins[i + 1]);
    }
    
    return max_mins;

} // static std::vector<long> riddleDS( ...

// Test case 6
TEST(RiddleTest, TestCase6) {
    const std::vector<long> input {2L, 6L, 1L, 12L};
    const std::vector<long> expected_output {12L, 2L, 1L, 1L};

    auto result = riddleFirstAttempt(input);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));

    result = riddleSecondAttempt(input);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));

    result = riddleDS(input);

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

    result = riddleSecondAttempt(input);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
    
    result = riddleDS(input);

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

    result = riddleSecondAttempt(input);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));

    result = riddleDS(input);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}