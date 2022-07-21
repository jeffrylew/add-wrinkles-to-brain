#include <gtest/gtest.h>

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <vector>

static int minimumAbsoluteDifferenceFirstAttempt(std::vector<int> arr)
{
    //! @details First attempt solution times out for Test cases 2 and 3

    // Keep track of minimum absolute difference
    // Initialize to largest integer value possible
    int min_abs_diff {std::numeric_limits<int>::max()};
    
    for (std::size_t i = 0; i < arr.size(); ++i)
    {
        for (std::size_t j = i + 1ULL; j < arr.size(); ++j)
        {
            const auto abs_diff = std::abs(arr.at(i) - arr.at(j));
            if (abs_diff < min_abs_diff)
            {
                min_abs_diff = abs_diff;
            }
        }
    }
    
    return min_abs_diff;

} // static int minimumAbsoluteDifferenceFirstAttempt( ...

//! @brief Solution from discussion section
//! @param[in] arr Vector of ints in [-1E9, 1E9] with size in [2, 1E5]
//! @return Minimum absolute difference between two elements
static int minimumAbsoluteDifferenceDiscussionSolution(std::vector<int> arr)
{
    // Keep track of minimum absolute difference
    // Initialize to largest integer value possible
    int min_abs_diff {std::numeric_limits<int>::max()};
    
    // Sort array first
    std::sort(arr.begin(), arr.end());

    for (std::size_t i = 1ULL; i < arr.size(); ++i)
    {
        const auto abs_diff = std::abs(arr.at(i) - arr.at(i - 1ULL));
        if (abs_diff < min_abs_diff)
        {
            min_abs_diff = abs_diff;

            if (0 == min_abs_diff)
            {
                break;
            }
        }
    }
    
    return min_abs_diff;

} // static int minimumAbsoluteDifferenceDiscussionSolution( ...

// Try sample input given in problem description
TEST(MinAbsDiffTest, SampleInput) {
    EXPECT_EQ(2, minimumAbsoluteDifferenceFirstAttempt({-2, 2, 4}));

    EXPECT_EQ(2, minimumAbsoluteDifferenceDiscussionSolution({-2, 2, 4}));
}

// Try Test case 0
TEST(MinAbsDiffTest, TestCase0) {
    EXPECT_EQ(3, minimumAbsoluteDifferenceFirstAttempt({3, -7, 0}));

    EXPECT_EQ(3, minimumAbsoluteDifferenceDiscussionSolution({3, -7, 0}));
}

// Try Test case 1
TEST(MinAbsDiffTest, TestCase1) {
    const std::vector<int> arr {
        -59, -36, -13, 1, -53, -92, -2, -96, -54, 75};
    
    EXPECT_EQ(1, minimumAbsoluteDifferenceFirstAttempt(arr));

    EXPECT_EQ(1, minimumAbsoluteDifferenceDiscussionSolution(arr));
}

// Try Test case 10
TEST(MinAbsDiffTest, TestCase10) {
    const std::vector<int> arr {1, -3, 71, 68, 17};

    EXPECT_EQ(3, minimumAbsoluteDifferenceFirstAttempt(arr));

    EXPECT_EQ(3, minimumAbsoluteDifferenceDiscussionSolution(arr));
}