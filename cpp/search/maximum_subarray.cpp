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

//! @brief Helper function for recursive solution
//! @param[in] nums     Reference to vector containing at least one number
//! @param[in] idx      Index of current element
//! @param[in] mustPick If true, pick current element and return 0 or recurse
//! @return Largest sum of contiguous subarray
static int maxSubArrayRecursive(const std::vector<int>& nums,
                                int                     idx,
                                bool                    mustPick)
{
    //! @details At each index idx, can either pick current element or not
    //!          If pick element then all future elements must be picked since
    //!          sub-array must be contiguous.
    //!          If picked any elements till now, can either end recursion by
    //!          returning sum formed till now or choose current element and
    //!          recurse further. This denotes two choices of choosing sub-array
    //!          formed from 1st picked element till now or expanding sub-array
    //!          by choosing current element.

    //! Sub-array must contain at least one element
    //! If mustPick is false at end, no element is picked - not a valid case
    if (idx >= static_cast<int>(nums.size()))
    {
        return mustPick ? 0 : -1e5;
    }
    
    if (mustPick)
    {
        //! Either stop here or choose current element and recurse
        return std::max(0,
                        nums[idx] + maxSubArrayRecursive(nums, idx + 1, true));
    }
    
    //! Try both choosing current element or not choosing
    return std::max(maxSubArrayRecursive(nums, idx + 1, false),
                    nums[idx] + maxSubArrayRecursive(nums, idx + 1, true));

} // static int maxSubArrayRecursive( ...

//! @brief Recursive solution from LC
//! @param[in] nums Vector containing at least one number
//! @return Largest sum of contiguous subarray
static int maxSubArrayRecursive(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/maximum-subarray/discuss/1595195/
    //!          C%2B%2BPython-7-Simple-Solutions-w-Explanation-or-Brute-Force-
    //!          %2B-DP-%2B-Kadane-%2B-Divide-and-Conquer
    //!
    //!          Time complexity O(N^2) since consider every subarray sum and
    //!          picking max. Space complexity O(N) for recursive stack space.
    //!          (Worse than Brute Force, which has space complexity O(1))

    return maxSubArrayRecursive(nums, 0, false);
}

//! @brief Helper function for dynamic programming with memoization solution
//! @param[in]     nums     Reference to vector containing at least one number
//! @param[in]     idx      Index of current element
//! @param[in]     mustPick If true, pick current element
//! @param[in,out] dp       dp[mustPick][idx] = max sum subarray starting at idx
//! @return Largest sum of contiguous subarray
static int maxSubArrayDPMemo(const std::vector<int>&        nums,
                             int                            idx,
                             bool                           mustPick,
                             std::vector<std::vector<int>>& dp)
{
    if (idx >= static_cast<int>(nums.size()))
    {
        return mustPick ? 0 : -1e5;
    }
    
    if (dp[mustPick][idx] != -1)
    {
        return dp[mustPick][idx];
    }

    if (mustPick)
    {
        return dp[mustPick][idx] =
            std::max(0, nums[idx] + maxSubArrayDPMemo(nums, idx + 1, true, dp));
    }
    
    return dp[mustPick][idx] =
        std::max(maxSubArrayDPMemo(nums, idx + 1, false, dp),
                 nums[idx] + maxSubArrayDPMemo(nums, idx + 1, true, dp));

} // static int maxSubArrayDPMemo( ...

//! @brief Dynamic programming with memoization solution from LC
//! @param[in] nums Vector containing at least one number
//! @return Largest sum of contiguous subarray
static int maxSubArrayDPMemo(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/maximum-subarray/discuss/1595195/
    //!          C%2B%2BPython-7-Simple-Solutions-w-Explanation-or-Brute-Force-
    //!          %2B-DP-%2B-Kadane-%2B-Divide-and-Conquer
    //!
    //!          Time complexity O(N) - calculate each state of dp (2N total)
    //!          and memoize result, returning them in future recursive calls.
    //!          Space complexity O(N) for recursive stack space.

    std::vector<std::vector<int>> dp(2, std::vector<int>(nums.size(), -1));
    return maxSubArrayDPMemo(nums, 0, false, dp);
}

//! @brief Dynamic programming tabulation solution from LC
//! @param[in] nums Vector containing at least one number
//! @return Largest sum of contiguous subarray
static int maxSubArrayDPTabulation(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/maximum-subarray/discuss/1595195/
    //!          C%2B%2BPython-7-Simple-Solutions-w-Explanation-or-Brute-Force-
    //!          %2B-DP-%2B-Kadane-%2B-Divide-and-Conquer
    //!
    //!          Time complexity O(N), iterate over nums once to compute dp
    //!          Space complexity O(N) for maintaining dp

    std::vector<std::vector<int>> dp(2, std::vector<int>(nums.size()));
    dp[0][0] = nums.front();
    dp[1][0] = nums.front();

    for (int i = 1; i < static_cast<int>(nums.size()); ++i)
    {
        //! dp[1][i] denotes max sub-array sum ending at i (including nums[i])
        //! Update as max between only picking current element nums[i] or
        //! extending from previous sub-array and choosing current nums[i] too
        //! i.e. dp[1][i - 1] + nums[i]
        //! This row can be removed in maxSubArrayDPIterative solution below
        dp[1][i] = std::max(nums[i], nums[i] + dp[1][i - 1]);

        //! dp[0][i] denotes max sub-array sum up to i (may not include nums[i])
        //! Update as max between sub-array sum up to last index dp[0][i - 1] or
        //! max sub-array sum found ending at current index dp[1][i]
        dp[0][i] = std::max(dp[0][i - 1], dp[1][i]);
    }
    return dp[0].back();

} // static int maxSubArrayDPTabulation( ...

//! @brief Dynamic programming, iterative solution from LC
//! @param[in] nums Vector containing at least one number
//! @return Largest sum of contiguous subarray
static int maxSubArrayDPIterative(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/maximum-subarray/discuss/1595195/
    //!          C%2B%2BPython-7-Simple-Solutions-w-Explanation-or-Brute-Force-
    //!          %2B-DP-%2B-Kadane-%2B-Divide-and-Conquer
    //!
    //!          Time complexity O(N). Iterate over nums once to compute dp and
    //!          once more over dp at end to find max sub-array sum.
    //!          Space complexity O(N) for maintaining dp

    auto dp = nums;
    for (int i = 1; i < static_cast<int>(nums.size()); ++i)
    {
        //! dp[1][i] from maxSubArrayDPTabulation solution above was the max
        //! sub-array sum ending at i. Store it in dp[i] and find the overall
        //! max sub-array sum at the end
        dp[i] = std::max(nums[i], nums[i] + dp[i - 1]);
    }
    return *std::max_element(dp.cbegin(), dp.cend());

} // static int maxSubArrayDPIterative( ...

//! @brief Another implementation of Kadane's Algorithm from LC
//! @param[in] nums Vector containing at least one number
//! @return Largest sum of contiguous subarray
static int maxSubArrayKadanesAlg(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/maximum-subarray/discuss/1595195/
    //!          C%2B%2BPython-7-Simple-Solutions-w-Explanation-or-Brute-Force-
    //!          %2B-DP-%2B-Kadane-%2B-Divide-and-Conquer
    //!
    //!          Time complexity O(N), iterating over nums once
    //!          Space complexity O(1) for constant extra space used (no dp vec)

    //! Max sub-array sum ending at i
    int currMax {};

    //! Max sub-array sum seen till now
    int maxTillNow {std::numeric_limits<int>::min()};

    //! Instead of maintaining dp vector of N elements, store max at each
    //! iteration instead of calculating it separately at the end
    for (auto i : nums)
    {
        currMax    = std::max(i, currMax + i);
        maxTillNow = std::max(maxTillNow, currMax);
    }

    return maxTillNow;

} // static int maxSubArrayKadanesAlg( ...

// LC Test case
TEST(MaxSubArrayTest, LCTest) {
    EXPECT_EQ(6, maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayDP({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayDC({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayRecursive({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayDPMemo({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayDPTabulation({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayDPIterative({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
    EXPECT_EQ(6, maxSubArrayKadanesAlg({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
}