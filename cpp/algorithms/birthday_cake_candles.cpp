#include <gtest/gtest.h>

#include <vector>

static int birthdayCakeCandles(std::vector<int> candles)
{
    int max_height {};
    int num_max {};
    
    for (const auto height : candles)
    {
        if (height > max_height)
        {
            max_height = height;
            num_max    = 1;
        }
        else if (height == max_height)
        {
            ++num_max;
        }
    }
    
    return num_max;
}

// Test case 0
TEST(BirthdayCakeCandlesTest, TestCase0) {
    EXPECT_EQ(2, birthdayCakeCandles({3, 2, 1, 3}));
}