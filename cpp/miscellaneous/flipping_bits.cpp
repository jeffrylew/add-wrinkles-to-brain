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

//! @brief Solution from HR discussion section
//! @param[in] n Number whose bits needs to be flipped
//! @return Number with flipped bits as a long
static long flippingBitsDS1(long n)
{
    //! @details https://www.hackerrank.com/challenges/flipping-bits/forum
    //!
    //! 2^32 - 1 = 4,294,967,296 - 1 = 1111 1111 1111 1111 1111 1111 1111 1111
    //! Flipping the bits is the same as subtracting from 2^32 - 1
    //!
    //! Smaller example:
    //!   2^4 - 1 = 15 = 1111
    //!   n = 9 = 1001
    //!   Flipped n = 0110 = 6
    //!   1111 - 1001 = 0110
    //!        15 - 9 = 6

    return static_cast<long>(std::pow(2.0, 32.0)) - 1L - n;
}

//! @brief Second solution from HR discussion section
//! @param[in] n Number whose bits needs to be flipped
//! @return Number with flipped bits as a long
static long flippingBitsDS2(long n)
{
    //! @details https://www.hackerrank.com/challenges/flipping-bits/forum
    //!
    //! 2^32 - 1 = 4,294,967,295 = 1111 1111 1111 1111 1111 1111 1111 1111
    //! Flipping the bits is the same as bitwise XOR with 2^32 - 1

    static const long all_ones {static_cast<long>(std::pow(2.0, 32.0)) - 1L};

    //! ^ = bitwise XOR
    return n ^ all_ones;
}

// Test case 0
TEST(FlippingBitsTest, TestCase0) {
    EXPECT_EQ(2147483648L, flippingBits(2147483647L));
    EXPECT_EQ(4294967294L, flippingBits(1L));
    EXPECT_EQ(4294967295L, flippingBits(0L));

    EXPECT_EQ(2147483648L, flippingBitsDS1(2147483647L));
    EXPECT_EQ(4294967294L, flippingBitsDS1(1L));
    EXPECT_EQ(4294967295L, flippingBitsDS1(0L));

    EXPECT_EQ(2147483648L, flippingBitsDS2(2147483647L));
    EXPECT_EQ(4294967294L, flippingBitsDS2(1L));
    EXPECT_EQ(4294967295L, flippingBitsDS2(0L));
}

// Test case 10
TEST(FlippingBitsTest, TestCase10) {
    EXPECT_EQ(4294967291L, flippingBits(4L));
    EXPECT_EQ(4294843839L, flippingBits(123456L));

    EXPECT_EQ(4294967291L, flippingBitsDS1(4L));
    EXPECT_EQ(4294843839L, flippingBitsDS1(123456L));

    EXPECT_EQ(4294967291L, flippingBitsDS2(4L));
    EXPECT_EQ(4294843839L, flippingBitsDS2(123456L));
}

// Test case 11
TEST(FlippingBitsTest, TestCase11) {
    EXPECT_EQ(4294967295L, flippingBits(0L));
    EXPECT_EQ(3492223820L, flippingBits(802743475L));
    EXPECT_EQ(4259365872L, flippingBits(35601423L));

    EXPECT_EQ(4294967295L, flippingBitsDS1(0L));
    EXPECT_EQ(3492223820L, flippingBitsDS1(802743475L));
    EXPECT_EQ(4259365872L, flippingBitsDS1(35601423L));

    EXPECT_EQ(4294967295L, flippingBitsDS2(0L));
    EXPECT_EQ(3492223820L, flippingBitsDS2(802743475L));
    EXPECT_EQ(4259365872L, flippingBitsDS2(35601423L));
}