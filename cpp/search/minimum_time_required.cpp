#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief First attempt solution times out for Test cases 5, 7-12
//! @param[in] machines Vector of machine rates (days to produce one item)
//! @param[in] goal     Number of items required to complete order
//! @return Minimum number of days required to complete the order
static long minTimeFirstAttempt(std::vector<long> machines, long goal)
{
    // Sort machines from highest (smallest value)
    // to lowest (largest value) rates
    std::sort(machines.begin(), machines.end());
    
    // Minimum number of days to complete the order
    // Initialize to highest rate in machines
    long min_days {machines.front()};
    
    // Current number of items produced
    long n_items {};
    
    while (n_items < goal)
    {
        for (const auto rate : machines)
        {
            // If min_days is a multiple of a machine rate
            // then an item has been produced
            if (0 == min_days % rate)
            {
                ++n_items;
            }
            
            if (n_items >= goal)
            {
                return min_days;
            }
            
        } // for (const auto rate : machines)
        
        // Increment the number of days
        ++min_days;
        
    } // while (n_items < goal)
    
    return min_days;

} // static long minTimeFirstAttempt( ...

// Try sample input given in problem description
TEST(MinTimeTest, SampleInput) {
    EXPECT_EQ(8L, minTimeFirstAttempt({2L, 3L, 2L}, 10L));
}

// Test case 0
TEST(MinTimeTest, TestCase0) {
    EXPECT_EQ(6L, minTimeFirstAttempt({2L, 3L}, 5L));
}

// Test case 1
TEST(MinTimeTest, TestCase1) {
    EXPECT_EQ(7L, minTimeFirstAttempt({1L, 3L, 4L}, 10L));
}

// Test case 13
TEST(MinTimeTest, TestCase13) {
    EXPECT_EQ(20L, minTimeFirstAttempt({4L, 5L, 6L}, 12L));
}