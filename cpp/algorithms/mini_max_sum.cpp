#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

static std::string miniMaxSum(std::vector<int> arr)
{
    std::sort(arr.begin(), arr.end());
    return std::to_string(std::accumulate(arr.cbegin(),
                                          std::prev(arr.cend()),
                                          0LL))
           + " "
           + std::to_string(std::accumulate(std::next(arr.cbegin()),
                                            arr.cend(),
                                            0LL));
}

//! @brief Solution from HR discussion section
//! @param[in] arr Vector of five integers
//! @return std::string containing min and max sums of 4 of 5 elements
static std::string miniMaxSumDS(std::vector<int> arr)
{
    long min {std::numeric_limits<long>::max()};
    long max {};
    long sum {};

    for (const auto ele : arr)
    {
        sum += ele;
        if (ele < min)
        {
            min = ele;
        }
        if (ele > max)
        {
            max = ele;
        }
    }

    return std::to_string(sum - max) + " " + std::to_string(sum - min);
}

// Test case 0
TEST(MiniMaxSumTest, TestCase0) {
    EXPECT_EQ("10 14", miniMaxSum({1, 2, 3, 4, 5}));
    EXPECT_EQ("10 14", miniMaxSumDS({1, 2, 3, 4, 5}));
}

// Test case 14
TEST(MiniMaxSumTest, TestCase14) {
    EXPECT_EQ("299 9271", miniMaxSum({7, 69, 2, 221, 8974}));
    EXPECT_EQ("299 9271", miniMaxSumDS({7, 69, 2, 221, 8974}));
}