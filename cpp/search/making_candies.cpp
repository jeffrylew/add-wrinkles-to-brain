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

//! @brief Converted Python solution from HR discussion section
//! @param[in] m Starting number of machines
//! @param[in] w Starting number of workers
//! @param[in] p Cost of new hire or new machine
//! @param[in] n Number of candies to produce
//! @return Minimum number of passes to accumulate at least n candies
static long minimumPassesDS2(long m, long w, long p, long n)
{
    //! @details https://www.hackerrank.com/challenges/making-candies/forum

    constexpr long max_long {std::numeric_limits<long>::max()};

    long candy {};
    long invest {};
    long spend {max_long};

    //! As long as we have fewer than n candies
    while (candy < n)
    {
        //! Calculate if we have enough candy to buy machines/workers
        //! If passes <= 0 then candy > p. Enough candy to buy (m * w) at least
        //! If passes > 0 then not enough candy. Continue creating candy at
        //! current rate until can afford a new worker/machines. i.e. p > candy,
        //! candy += [(p - candy) / (m * w)] * (m * w) = (p - candy)
        long passes = (p - candy) / (m * w);

        //! If can buy machines/workers then do so (greedy approach)
        if (passes <= 0)
        {
            //! Potential total number of machines and workers if candy was used
            //! We want to try to equal half machines/workers
            long mw   = (candy / p) + m + w;
            long half = static_cast<long>(std::ceil(mw / 2.0));

            //! Add to group with fewer resources until have m + w equal to mw
            if (m > w)
            {
                m = std::max(m, half);
                w = mw - m;
            }
            else
            {
                w = std::max(w, half);
                m = mw - w;
            }

            //! Save remaining candy that can't be spent on machines/workers
            candy = candy % p;

            //! In next step, add new production of candies for 1 pass
            passes = 1;
            
        } // if (passes <= 0)
        
        candy += passes * m * w;
        invest += passes;

        //! Save minimum between current saving strategy (not buying new machine
        //! or worker) and using investment
        const auto val = static_cast<long>(
            invest + std::ceil((n - candy) / (m * w * 1.0)));
        spend = std::min(spend, val);

    } // while (candy < n)
    
    return std::min(invest, spend);

} // static long minimumPassesDS2( ...

// Test case 0
TEST(MinmumPassesTest, TestCase0) {
    EXPECT_EQ(3L, minimumPassesFA(3L, 1L, 2L, 12L));
    EXPECT_EQ(3L, minimumPassesDS1(3L, 1L, 2L, 12L));
    EXPECT_EQ(3L, minimumPassesDS2(3L, 1L, 2L, 12L));
}

// Test case 1
TEST(MinmumPassesTest, TestCase1) {
    EXPECT_EQ(16L, minimumPassesFA(1L, 1L, 6L, 45L));
    EXPECT_EQ(16L, minimumPassesDS1(1L, 1L, 6L, 45L));
    EXPECT_EQ(16L, minimumPassesDS2(1L, 1L, 6L, 45L));
}

// Test case 2
TEST(MinmumPassesTest, TestCase2) {
    EXPECT_EQ(1L, minimumPassesFA(5184889632L, 5184889632L, 20L, 10000L));
    EXPECT_EQ(1L, minimumPassesDS1(5184889632L, 5184889632L, 20L, 10000L));
    EXPECT_EQ(1L, minimumPassesDS2(5184889632L, 5184889632L, 20L, 10000L));
}