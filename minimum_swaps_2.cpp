#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

//! @brief Determine minimum number of swaps to sort arr in ascending order
//! @param[in] arr Vector of ints passed by value
//! @return Minimum number of swaps to sort arr in ascending order
static int minimumSwaps(std::vector<int> arr) {
    // Total number of swaps
    int n_swaps {};
    
    // Map of integer elements to their indices in arr vector
    std::unordered_map<int, std::size_t> pos_map {};
    for (std::size_t i = 0; i < arr.size(); ++i)
    {
        pos_map.emplace(arr.at(i), i);
    }
    
    // Loop over arr again and swap as needed
    for (std::size_t i = 0; i < arr.size(); ++i)
    {
        // Value of element at current index i
        auto& curr_ele     = arr.at(i);
        auto& curr_ele_idx = pos_map.at(curr_ele);
        
        // If current element is in correct position, skip to next i
        if (curr_ele - 1 == static_cast<int>(i))
        {
            continue;
        }
        
        // Otherwise, find index of element that should at
        // this location if arr were sorted in ascending order
        const auto asc_order_ele_val = 1 + static_cast<int>(i);
        auto&      asc_order_ele_idx = pos_map.at(asc_order_ele_val);
        auto&      asc_order_ele     = arr.at(asc_order_ele_idx);
        
        // Swap element values and indices in arr and
        // pos_map respectively and increment number of swaps
        std::swap(curr_ele, asc_order_ele);
        std::swap(curr_ele_idx, asc_order_ele_idx);
        ++n_swaps;
    }
    
    return n_swaps;

} // static int minimumSwaps( ...

// Try sample input given in problem description
TEST(MinimumSwaps2Test, SampleInput) {
    EXPECT_EQ(5, minimumSwaps({7, 1, 3, 2, 4, 5, 6}));
}

// Try Test case 0
TEST(MinimumSwaps2Test, TestCase0) {
    EXPECT_EQ(3, minimumSwaps({4, 3, 1, 2}));
}

// Try Test case 1
TEST(MinimumSwaps2Test, TestCase1) {
    EXPECT_EQ(3, minimumSwaps({2, 3, 4, 1, 5}));
}

// Try Test case 2
TEST(MinimumSwaps2Test, TestCase2) {
    EXPECT_EQ(3, minimumSwaps({1, 3, 5, 2, 4, 6, 7}));
}