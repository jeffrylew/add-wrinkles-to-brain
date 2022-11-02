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

//! @brief Solution from HR discussion section
//! @param[in] candles Vector of candle heights
//! @return Number of candles that are tallest
static int birthdayCakeCandlesDS1(std::vector<int> candles)
{
    //! Max height and count of candles with max height
    int max {};
    int num_max {};

    for (const auto height : candles)
    {
        max < height ? num_max = !!(max = height) : num_max += max == height;
    }

    /*
     * Explanation of ternary below
     *
    for (const auto height : candles)
    {
        // Does height set a new record?
        if (max < height)
        {
            // Update max height
            max = height;

            // Reset counter to 1
            // !! converts any value different from 0 into 1
            num_max = 1;
        }
        else
        {
            // Check if current height is as tall as max
            if (max == height)
            {
                // Add 1 to counter if so, otherwise add 0
                ++num_max;
            }
            
        }
    }
     */

    return max;

} // static int birthdayCakeCandlesDS1( ...

//! @brief Another solution from HR discussion section, O(2n) time complexity
//! @param[in] candles Vector of candle heights
//! @return Number of candles that are tallest
static int birthdayCakeCandlesDS2(std::vector<int> candles)
{
    int max {candles.front()};
    int count {};
    
    const auto candles_size = static_cast<int>(candles.size());

    for (int i = 0; i < candles_size; ++i)
    {
        if (candles[i] > max)
        {
            max = candles[i];
        }
    }

    for (int i = 0; i < candles_size; ++i)
    {
        if (candles[i] == max)
        {
            ++count;
        }
    }

    return count;

} // static int birthdayCakeCandlesDS2( ...

// Test case 0
TEST(BirthdayCakeCandlesTest, TestCase0) {
    EXPECT_EQ(2, birthdayCakeCandles({3, 2, 1, 3}));
    EXPECT_EQ(2, birthdayCakeCandlesDS1({3, 2, 1, 3}));
    EXPECT_EQ(2, birthdayCakeCandlesDS2({3, 2, 1, 3}));
}