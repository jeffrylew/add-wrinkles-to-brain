#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <set>
#include <vector>

//! @brief First attempt solution times out for Test cases 6-16
//! @param[in] a Array of n elements
//! @param[in] m The modulo divisor
//! @return Maximum subarray sum modulo m
static long maximumSumFirstAttempt(std::vector<long> a, long m)
{
    //! Maximum subarray sum modulo m
    long max_sum_modulo {};
    
    //! Max possible modulo is one less than modulo divisor m
    const long max_modulo {m - 1L};
    
    const auto a_size = static_cast<int>(a.size());
    
    //! Size of current subarray
    int subarr_size {1};
    
    //! Sums of increasing subarray sizes starting at each index
    std::vector<long> subarr_sums(a_size);
    
    while (subarr_size <= a_size)
    {
        //! Start index in a
        int start_idx {};
        
        while (start_idx + subarr_size <= a_size)
        {
            //! Update subarr_sums as the subarray size increases
            subarr_sums[start_idx] += a[start_idx + subarr_size - 1];
            
            const auto curr_subarr_modulo = subarr_sums[start_idx] % m;
            
            if (max_modulo == curr_subarr_modulo)
            {
                return curr_subarr_modulo;
            }
            else if (max_sum_modulo < curr_subarr_modulo)
            {
                max_sum_modulo = curr_subarr_modulo;
            }
            
            ++start_idx;
            
        } // while (start_idx + ...
        
        ++subarr_size;
        
    } // while (subarr_size <= ...
    
    return max_sum_modulo;

} // static long maximumSumFirstAttempt( ...

//! @brief Solution from HR discussion section
//! @param[in] a Array of n elements
//! @param[in] m The modulo divisor
//! @return Maximum subarray sum modulo m
static long maximumSumDiscussionSolution(std::vector<long> a, long m)
{
    //! @details
    //!     https://www.hackerrank.com/challenges/maximum-subarray-sum/forum

    long sum {};
    long max {std::numeric_limits<long>::min()};
    long result {std::numeric_limits<long>::max()};
    
    std::set<long> s {};
    
    //! From explanation at https://www.quora.com/
    //!     What-is-the-logic-used-in-the-HackerRank-Maximise-Sum-problem
    //! Quora answer defines
    //!     prefix[n] = (a[0] + a[1] + ... + a[n]) % m
    //! And the provided code is
    //!     int curr = 0;
    //!     for (int i = 0; i < n; ++i) {
    //!         curr = (curr + a[i] % m) % m;
    //!         prefix[i] = curr;
    //!     }
    //! For two elements it can be proved
    //!     (a[0] + a[1]) % m = (a[0] % m + a[1] % m) % m
    //! For three elements it can be proved
    //!     (a[0] + a[1] + a[2]) % m = (a[0] % m + a[1] % m + a[2] % m) % m
    //! The code above matches this
    //!     i = 0: curr = (0 + a[0] % m) % m = a[0] % m
    //!            prefix[0] = a[0] % m
    //!     i = 1: curr = (a[0] % m + a[1] % m) % m, equal to (a[0] + a[1]) % m
    //!            prefix[1] = (a[0] % m + a[1] % m) % m
    //!     i = 2: curr = [(a[0] % m + a[1] % m) % m + a[2] % m] % m
    //!                 = [(a[0] + a[1]) % m + a[2] % m] % m
    //!            Let alpha = (a[0] + a[1]). Then
    //!            curr = [alpha % m + a[2] % m] % m
    //!                 = [alpha + a[2]] % m
    //!                 = [(a[0] + a[1]) + a[2]] % m
    //!
    //! Need to confirm if code in loop below matches the above
    for (auto& ele : a)
    {
        sum = (sum + ele) % m;
        ele = sum;
        max = std::max(max, sum);
    }
    
    for (auto x : a)
    {
        auto p = s.insert(x);
        if (++p.first != s.end())
        {
            result = std::min(*p.first - x, result);
        }
    }
    
    return std::max(max, m - result);

} // static long maximumSumDiscussionSolution( ...

// Test case 0
TEST(MaximumSumTest, TestCase0) {
    EXPECT_EQ(6L, maximumSumFirstAttempt({3L, 3L, 9L, 9L, 5L}, 7L));
    EXPECT_EQ(6L, maximumSumDiscussionSolution({3L, 3L, 9L, 9L, 5L}, 7L));
}

// Test case 17
TEST(MaximumSumTest, TestCase17) {
    EXPECT_EQ(1L, maximumSumFirstAttempt({1L, 2L, 3L}, 2L));
    EXPECT_EQ(1L, maximumSumDiscussionSolution({1L, 2L, 3L}, 2L));
}

// Test case 18
TEST(MaximumSumTest, TestCase18) {
    EXPECT_EQ(4L, maximumSumFirstAttempt({1L, 5L, 9L}, 5L));
    EXPECT_EQ(4L, maximumSumDiscussionSolution({1L, 5L, 9L}, 5L));
}