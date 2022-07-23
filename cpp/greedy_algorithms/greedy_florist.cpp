#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static int getMinimumCost(int k, std::vector<int> c)
{
    // Keep track of cost
    int min_cost {};
    
    // Keep track of number of flowers each buys
    std::vector<int> n_flowers(static_cast<std::size_t>(k));
    
    // Sort flowers in descending order of cost
    std::sort(c.begin(), c.end(), std::greater<int> {});
    
    // Iterate over flower costs and calculate costs
    for (std::size_t i = 0; i < c.size(); ++i)
    {
        // Determine which person is buying flower i
        const auto person = i % static_cast<std::size_t>(k);
        
        min_cost += (n_flowers.at(person) + 1) * c.at(i);
        
        // Increment number of flower purchased by each person
        ++n_flowers.at(person);
        
    } // for (std::size_t i = 0; ...
    
    return min_cost;

} // static int getMinimumCost( ...

// Try sample input given in problem description
TEST(GetMinimumCostTest, SampleInput) {
    EXPECT_EQ(11, getMinimumCost(3, {1, 2, 3, 4}));
}

// Test case 0
TEST(GetMinimumCostTest, TestCase0) {
    EXPECT_EQ(13, getMinimumCost(3, {2, 5, 6}));
}

// Test case 10
TEST(GetMinimumCostTest, TestCase10) {
    EXPECT_EQ(15, getMinimumCost(2, {2, 5, 6}));
}

// Test case 11
TEST(GetMinimumCostTest, TestCase11) {
    EXPECT_EQ(29, getMinimumCost(3, {1, 3, 5, 7, 9}));
}