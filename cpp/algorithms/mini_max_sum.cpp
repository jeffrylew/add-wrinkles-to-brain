#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
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

// Test case 0
TEST(MiniMaxSumTest, TestCase0) {
    EXPECT_EQ("10 14", miniMaxSum({1, 2, 3, 4, 5}));
}

// Test case 14
TEST(MiniMaxSumTest, TestCase14) {
    EXPECT_EQ("299 9271", miniMaxSum({7, 69, 2, 221, 8974}));
}