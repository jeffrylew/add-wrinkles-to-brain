#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>

//! @brief Discussion solution for largest rectangle using a stack
//! @param[in] h Vector of building heights
//! @return Area of largest rectangle as a long
static long largestRectangleDiscussionSolution(std::vector<int> h)
{
    //! @details Referenced the following:
    //!          https://www.hackerrank.com/challenges/largest-rectangle/forum
    //!          https://youtu.be/ZmnqCZp9bBs
    //!          https://youtu.be/zx5Sw9130L0
    //!
    //!          Same problem as
    //!          https://leetcode.com/problems/largest-rectangle-in-histogram/
    //!
    //!          Time complexity: O(n)
    //!            - Only iterated through vector h once
    //!            - Pushed and popped each element onto/from stack once
    //!          Space complexity: O(n)
    //!            - Stack could contain up to size of vector h elements

    long max_area {};
    
    // Keep track of building <index, height>
    std::stack<std::pair<std::size_t, int>> idx_height {};
    
    for (std::size_t i = 0; i < h.size(); ++i)
    {
        const auto curr_height = h.at(i);
        auto       start_idx   = i;

        while (not idx_height.empty() && idx_height.top().second > curr_height)
        {
            // Need to
            //   - pop top height from stack
            //   - check max area that can be created from stack top's height
            //   - extend start index of rectangle from current height backwards
            std::size_t top_idx {};
            int         top_height {};
            
            std::tie(top_idx, top_height) = idx_height.top();
            idx_height.pop();

            // Calculate max area. Width is (current index i - top index)
            const auto stack_top_area =
                static_cast<long>(top_height) * static_cast<long>(i - top_idx);
            max_area = std::max(stack_top_area, max_area);

            // Stack top height is greater than current height at idx i
            // Can extend start_idx backwards to stack top index that was popped
            start_idx = top_idx;

        } // while (not idx_height.empty() && ...
        
        // Not just adding index i. Use start_idx that was extended backwards
        idx_height.emplace(start_idx, curr_height);

    } // for (std::size_t i = 0; ...
    
    // There may be entries left in stack. These extend to the end
    while (not idx_height.empty())
    {
        std::size_t top_idx {};
        int         top_height {};
        
        std::tie(top_idx, top_height) = idx_height.top();
        idx_height.pop();

        // Calculate max area. Width is (length of h - top index)
        const auto h_size = h.size();
        const auto stack_top_area =
            static_cast<long>(top_height) * static_cast<long>(h_size - top_idx);
        max_area = std::max(stack_top_area, max_area);

    } // while (not idx_height.empty())

    return max_area;

} // static long largestRectangleDiscussion Solution( ...

// Try sample input given in problem description
TEST(LargestRectangleTest, SampleInput) {
    EXPECT_EQ(6L, largestRectangleDiscussionSolution({3, 2, 3}));
}

// Test case 0
TEST(LargestRectangleTest, TestCase0) {
    EXPECT_EQ(9L, largestRectangleDiscussionSolution({1, 2, 3, 4, 5}));
}

// Test case 14
TEST(LargestRectangleTest, TestCase14) {
    EXPECT_EQ(18L, largestRectangleDiscussionSolution({1, 3, 5, 9, 11}));
}

// Test case 15
TEST(LargestRectangleTest, TestCase15) {
    EXPECT_EQ(50L, largestRectangleDiscussionSolution({11, 11, 10, 10, 10}));
}