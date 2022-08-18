#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Discussion solution for max sum of subset of non-adjacent elements
//! @param[in] arr Vector of integers
//! @return Max sum of subset of non-adjacent elements
static int maxSubsetSumDiscussionSolution(std::vector<int> arr)
{
    //! Keep track of maximum sum at each position in arr
    std::vector<int> max_sum_arr(arr.size());
    
    //! Max sum at index 0 is element value
    max_sum_arr[0] = arr.front();
    
    if (arr.size() < 2ULL)
    {
        return max_sum_arr.front();
    }
    
    //! Max sum at index 1 is max(arr[0], arr[1])
    max_sum_arr[1] = std::max(arr[0], arr[1]);
    
    //! Iterate through remainder of vector
    for (int i = 2; i < static_cast<int>(arr.size()); ++i)
    {
        const auto curr_ele        = arr[i];
        const auto last_max_sum    = max_sum_arr[i - 1];
        const auto non_adj_max_sum = max_sum_arr[i - 2];
        
        //! Max sum at index i is max of
        //! - last max sum (e.g. arr[0] < 0, arr[1] > 0, arr[2] = 0 -> max @ 1)
        //! - current element value (max sum two indices prior could be < 0)
        //! - current element value + last max sum
        max_sum_arr[i] = std::max({last_max_sum,
                                   curr_ele,
                                   curr_ele + non_adj_max_sum});
        
    } // for (int i = 2; ...
    
    return max_sum_arr.back() < 0 ? 0 : max_sum_arr.back();

} // static int maxSubsetSumDiscussionSolution( ...

// Test case 30
TEST(MaxSubsetSumTest, TestCase30) {
    EXPECT_EQ(13, maxSubsetSumDiscussionSolution({3, 7, 4, 6, 5}));
}

// Test case 31
TEST(MaxSubsetSumTest, TestCase31) {
    EXPECT_EQ(11, maxSubsetSumDiscussionSolution({2, 1, 5, 8, 4}));
}

// Test case 32
TEST(MaxSubsetSumTest, TestCase32) {
    EXPECT_EQ(15, maxSubsetSumDiscussionSolution({3, 5, -7, 8, 10}));
}