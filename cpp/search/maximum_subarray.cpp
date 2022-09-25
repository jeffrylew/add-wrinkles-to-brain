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

// LC Test case
TEST(MaxSubArrayTest, LCTest) {
    EXPECT_EQ(6, maxSubArray({-2, 1, -3, 4, -1, 2, 1, -5, 4}));
}