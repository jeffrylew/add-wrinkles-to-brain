#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief From LC, find contiguous subarray which has largest sum
//! @param[in] nums Vector containing at least one number
//! @return Largest sum of contiguous subarray
static int maxSubArray(std::vector<int> nums)
{
    //! @details Kadane's Algorithm, https://www.youtube.com/watch?v=86CQq3pKSUw

    int max_current {nums.front()};
    int max_global {nums.front()};

    for (auto it = nums.cbegin() + 1; it != nums.cend(); ++it)
    {
        max_current = std::max(*it, max_current + *it);
        if (max_current > max_global)
        {
            max_global = max_current;
        }
    }

    return max_global;

} // static int maxSubArray( ...

//! @brief Dynamic programming solution from LC
//! @param[in] nums Vector containing at least one number
//! @return Largest sum of contiguous subarray
static int maxSubArrayDP(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/maximum-subarray/discuss/20193/
    //!          DP-solution-and-some-thoughts
    //!
    //! Idea using O(n) space (less efficient than Kadane's Algorithm) is
    //!     maxSubArrayDP(nums, i) = nums[i] + (maxSubArrayDP(nums, i - 1) > 0)
    //!         ? maxSubArrayDP(nums, i - 1) : 0;

    std::vector<int> dp(nums.size());
    dp[0] = nums.front();

    int max = dp[0];

    for (int i = 1; i < static_cast<int>(nums.size()); ++i)
    {
        dp[i] = nums[i] + (dp[i - 1] > 0 ? dp[i - 1] : 0);
        max   = std::max(max, dp[i]);
    }
    
    return max;

} // static int maxSubArrayDP( ...

// LC Test case
TEST(MaxSubArrayTest, LCTest) {
    EXPECT_EQ(6, maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayDP({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
}