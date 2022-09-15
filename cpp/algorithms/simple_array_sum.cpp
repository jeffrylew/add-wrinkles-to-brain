#include <gtest/gtest.h>

#include <numeric>
#include <vector>

static int simpleArraySum(std::vector<int> ar)
{
    return std::accumulate(ar.cbegin(), ar.cend(), 0);
}

// Test case 0
TEST(SimpleArraySumTest, TestCase0) {
    EXPECT_EQ(31, simpleArraySum({1, 2, 3, 4, 10, 11}));
}