#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
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

//! @brief Helper function for divide and conquer solution (recursive)
//! @param[in] nums Reference to vector containing at least one number
//! @param[in] l    Left index to search from
//! @param[in] r    Right index to search from
//! @return Largest sum of contiguous subarray
static int maxSubArrayDC(const std::vector<int>& nums, int l, int r)
{
    //! @details Idea is to break nums into halves and find max sub-array sum in
    //!          them recursively. Tricky part is to handle case where max
    //!          sub-array sum spans both halves. For this case, use a linear
    //!          algorithm. Start from middle element and move to right and left
    //!          ends, recording maximum sums on either side. The max sub-array
    //!          sum is equal to middle element plus latter two values.
    //!
    //!          O(nlog(n)) time complexity. For loop inside recursion can be
    //!          O(n) in worst case. There are log(n) levels in recursion tree.

    if (l > r)
    {
        return std::numeric_limits<int>::min();
    }
    
    //! Middle element index
    int m {l + (r - l) / 2};

    //! Max sub-array sum on LHS of middle element
    int ml {};

    //! Max sub-array sum on RHS of middle element
    int mr {};

    //! Find max sub-array sum on LHS, excluding middle element
    int lmax = maxSubArrayDC(nums, l, m - 1);

    //! Find max sub-array sum on RHS, excluding middle element
    int rmax = maxSubArrayDC(nums, m + 1, r);

    //! Handle LHS for max sub-array spanning both halves
    int sum {};
    for (int i = m - 1; i >= l; --i)
    {
        sum += nums[i];
        ml = std::max(sum, ml);
    }
    
    //! Handle RHS for max sub-array spanning both halves
    sum = 0;
    for (int i = m + 1; i <= r; ++i)
    {
        sum += nums[i];
        mr = std::max(sum, mr);
    }
    
    return std::max(std::max(lmax, rmax), ml + nums[m] + mr);

} // static int maxSubArrayDC( ...

//! @brief Divide and conquer solution from LC
//! @param[in] nums Vector containing at least one number
//! @return Largest sum of contiguous subarray
static int maxSubArrayDC(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/maximum-subarray/discuss/20452/
    //!          C%2B%2B-DP-and-Divide-and-Conquer

    return maxSubArrayDC(nums, 0, static_cast<int>(nums.size()) - 1);
}

// LC Test case
TEST(MaxSubArrayTest, LCTest) {
    EXPECT_EQ(6, maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayDP({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayDC({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
}