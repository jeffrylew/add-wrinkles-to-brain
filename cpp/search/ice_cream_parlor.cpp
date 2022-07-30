#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

static std::pair<std::size_t, std::size_t> whatFlavors(std::vector<int> cost,
                                                       int              money)
{
    // Map of ice cream prices to their 1-based indices
    std::unordered_map<int, std::size_t> price_idx {};
    
    for (std::size_t i = 0; i < cost.size(); ++i)
    {
        const auto curr_cost = cost.at(i);
        
        // Check if map contains another ice cream cost
        // that would satisfy total money spent
        const auto remaining_cost    = money - curr_cost;
        auto       remaining_cost_it = price_idx.find(remaining_cost);
        if (remaining_cost_it != price_idx.cend()) 
        {
            // Since we check for an existing cost entry in the map,
            // this logic will handle the case when curr_cost == remaining_cost
            return {std::min(i + 1UL, remaining_cost_it->second),
                    std::max(i + 1UL, remaining_cost_it->second)};
        }
        
        // Add ice cream cost and its index to map
        price_idx[curr_cost] = i + 1ULL;
        
    } // for (std::size_t i = 0; i < cost.size(); ++i)
    
    // There will always be a unique solution so nothing to do here
    // But should silence -Wreturn-type control reaches end of non-void function
    return {0, 0};

} // static std::pair<std::size, std::size_t> whatFlavors( ...

// Try sample input given in problem description
TEST(WhatFlavorsTest, SampleInput) {
    const auto ret = whatFlavors({2, 1, 3, 5, 6}, 5);
    EXPECT_EQ(ret.first, 1ULL);
    EXPECT_EQ(ret.second, 3ULL);
}

// Test case 14
TEST(WhatFlavorsTest, TestCase14) {
    auto ret = whatFlavors({1, 4, 5, 3, 2}, 4);
    EXPECT_EQ(ret.first, 1ULL);
    EXPECT_EQ(ret.second, 4ULL);

    ret = whatFlavors({2, 2, 4, 3}, 4);
    EXPECT_EQ(ret.first, 1ULL);
    EXPECT_EQ(ret.second, 2ULL);
}

// Test case 15
TEST(WhatFlavorsTest, TestCase15) {
    const auto ret = whatFlavors({1, 2, 3, 5, 6}, 5);
    EXPECT_EQ(ret.first, 2ULL);
    EXPECT_EQ(ret.second, 3ULL);
}

// Test case 16
TEST(WhatFlavorsTest, TestCase16) {
    auto ret = whatFlavors({4, 3, 2, 5, 7}, 8);
    EXPECT_EQ(ret.first, 2ULL);
    EXPECT_EQ(ret.second, 4ULL);

    ret = whatFlavors({7, 2, 5, 4, 11}, 12);
    EXPECT_EQ(ret.first, 1ULL);
    EXPECT_EQ(ret.second, 3ULL);
}