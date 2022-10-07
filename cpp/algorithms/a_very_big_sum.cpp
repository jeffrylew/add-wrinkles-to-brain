#include <gtest/gtest.h>

#include <numeric>
#include <vector>

//! @brief Return sum of elements in vector
//! @param[in] ar Vector of longs to sum
//! @return Sum of all vector elements
static long aVeryBigSum(std::vector<long> ar)
{
    return std::accumulate(ar.cbegin(), ar.cend(), 0L);
}

// Test case 0
TEST(AVeryBigSumTest, TestCase0) {
    EXPECT_EQ(5000000015L, aVeryBigSum({1000000001L,
                                        1000000002L,
                                        1000000003L,
                                        1000000004L,
                                        1000000005L}));
}