#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <vector>

//! @brief First attempt solution only passes Test cases 0, 10, 12, 16
static long candiesFirstAttempt(int n, std::vector<int> arr)
{
    //! Less than two children case
    if (1 == n)
    {
        return 1L;
    }
    
    //! Number of candies per child
    std::vector<long> candies_per_child(static_cast<std::size_t>(n));
    
    //! Determine number of candies for first two children
    candies_per_child[0] = (arr[0] >= arr[1]) ? 2L : 1L;
    candies_per_child[1] = (arr[0] >= arr[1]) ? 1L : 2L;
    
    //! Loop over remaining children
    for (std::size_t i = 2ULL; i < arr.size(); ++i)
    {
        if (arr[i] > arr[i - 1ULL])
        {
            candies_per_child[i] = candies_per_child[i - 1ULL] + 1L;
        }
        else
        {
            //! Case: arr[i] <= arr[i - 1]
            
            if (candies_per_child[i - 1ULL] > 1)
            {
                //! Set child i's candies to 1
                //! The logic in the else block below will increment
                //! this number as needed
                candies_per_child[i] = 1L;
            }
            else
            {
                //! Encountered lower rating but need to give at least
                //! one candy to each child so iterate backwards and
                //! increment candies while the number of candies is
                //! monotonically increasing
                candies_per_child[i] = 1L;
                
                int j = static_cast<int>(i) - 1;
                while (j >= 0)
                {
                    if (candies_per_child[j] >= candies_per_child[j + 1])
                    {
                        ++candies_per_child[j];
                        --j;
                    }
                    else
                    {
                        // Encountered a decreasing number of candies
                        break;
                    }
                }
                
                //! Number of candies at j + 1 needs to be decremented
                //! since it does not participate in the increasing range
                //! This part is sketchy and probably incorrect
                --candies_per_child[j + 1];
                
            } // else -> if (candies_per_child[i - 1ULL] > 1)
            
        } // else -> if (arr[i] > arr[i - 1ULL])
        
    } // for (std::size_t i = 2ULL; ...
    
    return std::accumulate(candies_per_child.cbegin(),
                           candies_per_child.cend(),
                           0L);

} // static long candiesFirstAttempt( ...

//! @brief LC discussion solution with O(n) space
//! @param[in] n   Number of children in class
//! @param[in] arr Vector of student ratings
//! @return Minimum number of candies to buy
static long candiesLCDiscussionSolution_O_n(int n, std::vector<int> arr)
{
    //! @details https://leetcode.com/problems/candy/discuss/42769/
    //!          A-simple-solution
    //!
    //!          O(n) time and O(n) space

    //! Less than two children case
    if (n <= 1)
    {
        return 1L;
    }

    //! Number of candies per child, initialized with 1
    std::vector<long> candies_per_child(static_cast<std::size_t>(n), 1L);

    //! Ensure children with higher rating get more candy than left peer
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] > arr[i - 1])
        {
            //! i - 1 = left peer, i = current child
            candies_per_child[i] = candies_per_child[i - 1] + 1L;
        }
    }

    //! Ensure children with higher rating get more candy than right peer
    for (int i = n - 1; i > 0; --i)
    {
        if (arr[i - 1] > arr[i])
        {
            //! i = right peer, i - 1 = current child
            candies_per_child[i - 1] = std::max(candies_per_child[i] + 1L,
                                                candies_per_child[i - 1]);
        }
    }
    
    return std::accumulate(candies_per_child.cbegin(),
                           candies_per_child.cend(),
                           0L);

} // static long candiesLCDiscussionSolution_O_n( ...

// Test case 0
TEST(CandiesTest, TestCase0) {
    EXPECT_EQ(4L, candiesFirstAttempt(3, {1, 2, 2}));
    EXPECT_EQ(4L, candiesLCDiscussionSolution_O_n(3, {1, 2, 2}));
}

// Test case 10
TEST(CandiesTest, TestCase10) {
    std::vector<int> arr {
        2, 4, 2, 6, 1, 7, 8, 9, 2, 1};
    
    EXPECT_EQ(19L, candiesFirstAttempt(10, arr));
    EXPECT_EQ(19L, candiesLCDiscussionSolution_O_n(10, arr));
}

// Test case 16
TEST(CandiesTest, TestCase16) {
    std::vector<int> arr {
        2, 4, 3, 5, 2, 6, 4, 5};
    
    EXPECT_EQ(12L, candiesFirstAttempt(8, arr));
    EXPECT_EQ(12L, candiesLCDiscussionSolution_O_n(8, arr));
}