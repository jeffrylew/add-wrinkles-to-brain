#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <limits>

//! @brief First attempt soln fails test cases 4, 7-10, 12-14, 16-24, 30, 37, 38
//! @param[in] m Starting number of machines
//! @param[in] w Starting number of workers
//! @param[in] p Cost of new hire or new machine
//! @param[in] n Number of candies to produce
//! @return Minimum number of passes to accumulate at least n candies
static long minimumPassesFA(long m, long w, long p, long n)
{
    long min_passes {};
    long num_candies {};
    
    while (num_candies < n)
    {
        num_candies += m * w;
        
        //! If number of candies produced is less than half of desired amount,
        //! increase number of machines and workers
        if (num_candies < n / 2)
        {
            while (num_candies - p >= 0)
            {
                num_candies -= p;
                
                //! Increase smaller of machines/workers
                if (m <= w)
                {
                    ++m;
                }
                else
                {
                    ++w;
                }
            }
        }
        
        ++min_passes;
    }
    
    return min_passes;

} // static long minimumPassesFA( ...

//! @brief Solution from HR discussion section
//! @param[in] m Starting number of machines
//! @param[in] w Starting number of workers
//! @param[in] p Cost of new hire or new machine
//! @param[in] n Number of candies to produce
//! @return Minimum number of passes to accumulate at least n candies
static long minimumPassesDS1(long m, long w, long p, long n)
{
    //! @details https://www.hackerrank.com/challenges/making-candies/forum

    constexpr long max_long {std::numeric_limits<long>::max()};

    long passes {};
    long candy {};
    long run {max_long};
    long step {};

    while (candy < n)
    {
        step = (m > max_long / w) ? 0 : (p - candy) / (m * w);

        if (step <= 0)
        {
            long mw = candy / p;

            if (m >= w + mw)
            {
                w += mw;
            }
            else if (w >= m + mw)
            {
                m += mw;
            }
            else
            {
                long total = m + w + mw;
                m = total / 2;
                w = total - m;
            }

            candy = candy % p;
            step = 1;

        } // if (step <= 0)
        
        passes += step;

        if (step * m > max_long / w)
        {
            candy = max_long;
        }
        else
        {
            candy += step * m * w;

            const auto val = static_cast<long>(
                passes + std::ceil((n - candy) / (m * w * 1.0)));

            run = std::min(run, val);
        }

    } // while (candy < n)
    
    return std::min(passes, run);

} // static long minimumPassesDS1( ...

// Test case 0
TEST(MinmumPassesTest, TestCase0) {
    EXPECT_EQ(3L, minimumPassesFA(3L, 1L, 2L, 12L));
    EXPECT_EQ(3L, minimumPassesDS1(3L, 1L, 2L, 12L));
}

// Test case 1
TEST(MinmumPassesTest, TestCase1) {
    EXPECT_EQ(16L, minimumPassesFA(1L, 1L, 6L, 45L));
    EXPECT_EQ(16L, minimumPassesDS1(1L, 1L, 6L, 45L));
}

// Test case 2
TEST(MinmumPassesTest, TestCase2) {
    EXPECT_EQ(1L, minimumPassesFA(5184889632L, 5184889632L, 20L, 10000L));
    EXPECT_EQ(1L, minimumPassesDS1(5184889632L, 5184889632L, 20L, 10000L));
}