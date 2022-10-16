#include <gtest/gtest.h>

#include <cmath>

static long flippingBits(long n)
{
    long output {};
    
    for (long i = 0L; i < 32L; ++i)
    {
        long div_by_2 {n / 2};
        bool remainder {static_cast<bool>(n % 2)};
        
        output += static_cast<long>(not remainder)
                * static_cast<long>(std::pow(2L, i));
        
        n = div_by_2;
    }
    
    return output;
}

// Test case 0
TEST(FlippingBitsTest, TestCase0) {
    EXPECT_EQ(2147483648L, flippingBits(2147483647L));
    EXPECT_EQ(4294967294L, flippingBits(1L));
    EXPECT_EQ(4294967295L, flippingBits(0L));
}

// Test case 10
TEST(FlippingBitsTest, TestCase10) {
    EXPECT_EQ(4294967291L, flippingBits(4L));
    EXPECT_EQ(4294843839L, flippingBits(123456L));
}

// Test case 11
TEST(FlippingBitsTest, TestCase11) {
    EXPECT_EQ(4294967295L, flippingBits(0L));
    EXPECT_EQ(3492223820L, flippingBits(802743475L));
    EXPECT_EQ(4259365872L, flippingBits(35601423L));
}