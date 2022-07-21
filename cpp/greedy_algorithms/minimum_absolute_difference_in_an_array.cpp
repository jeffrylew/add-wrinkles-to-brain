#include <gtest/gtest.h>

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

// Try sample input given in problem description
TEST(MinAbsDiffTest, SampleInput) {
    EXPECT_EQ(2, minimumAbsoluteDifferenceFirstAttempt({-2, 2, 4}));
}

// Try Test case 0
TEST(MinAbsDiffTest, TestCase0) {
    EXPECT_EQ(3, minimumAbsoluteDifferenceFirstAttempt({3, -7, 0}));
}

// Try Test case 1
TEST(MinAbsDiffTest, TestCase1) {
    const std::vector<int> arr {
        -59, -36, -13, 1, -53, -92, -2, -96, -54, 75};
    EXPECT_EQ(1, minimumAbsoluteDifferenceFirstAttempt(arr));
}

// Try Test case 10
TEST(MinAbsDiffTest, TestCase10) {
    EXPECT_EQ(3, minimumAbsoluteDifferenceFirstAttempt({1, -3, 71, 68, 17}));
}