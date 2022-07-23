#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <vector>

static int maxMin(int k, std::vector<int> arr)
{
    // Minimum possible unfairness initialized with max int value
    int min_unfairness {std::numeric_limits<int>::max()};
    
    // Sort arr in ascending order
    std::sort(arr.begin(), arr.end());
    
    // Get iterators to minimum and maximum elements
    auto it_min = arr.cbegin();
    auto it_max = arr.cbegin() + (k - 1);
    
    // Iterate through sorted arr and determine min unfairness
    while (it_max != arr.cend())
    {
        const auto diff = *it_max - *it_min;
        if (0 == diff)
        {
            // Difference between two elements cannot be
            // less than zero so return immediately
            return 0;
        }
        
        // If found a difference less than current min
        // then update min_unfairness
        if (diff < min_unfairness)
        {
            min_unfairness = diff;
        }
        
        // Shift iterators
        ++it_min;
        ++it_max;
        
    } // while (it_max != arr.cend())
    
    return min_unfairness;

} // static int maxMin( ...

// Try sample input given in problem description
TEST(MaxMinTest, SampleInput) {
    EXPECT_EQ(1, maxMin(2, {1, 4, 7, 2}));
}

// Test case 0
TEST(MaxMinTest, TestCase0) {
    EXPECT_EQ(20, maxMin(3, {10, 100, 300, 200, 1000, 20, 30}));
}

// Test case 1
TEST(MaxMinTest, TestCase1) {
    EXPECT_EQ(3, maxMin(4, {1, 2, 3, 4, 10, 20, 30, 40, 100, 200}));
}

// Test case 15
TEST(MaxMinTest, TestCase15) {
    EXPECT_EQ(0, maxMin(2, {1, 2, 1, 2, 1}));
}