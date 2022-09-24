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
    //! Code below for a = [3, 3, 9, 9, 5] and m = 7
    //!     i = 0: sum = (0 + a[0]) % m = a[0] % m = 3
    //!            a[0] = a[0] % m = 3
    //!            max = max[-LONG_MIN, a[0] % m] = a[0] % m = 3
    //!     i = 1: sum = (a[0] % m + a[1]) % m = (3 + 3) % 7 = 6
    //!            a[1] = (a[0] % m + a[1]) % m = 6
    //!            max = max[a[0] % m = 3, (a[0] % m + a[1]) % m = 6] = 6
    //!     i = 2: sum = [(a[0] % m + a[1]) % m + a[2]] % m = (6 + 9) % 7 = 1
    //!            a[2] = [(a[0] % m + a[1]) % m + a[2]] % m = 1
    //!            max = max[(a[0] % m + a[1]) % m = 6,
    //!                      [(a[0] % m + a[1]) % m + a[2]] % m = 1] = 6
    //!     i = 3: sum = [[(a[0] % m + a[1]) % m + a[2]] % m + a[3]] % m
    //!                = (1 + 9) % 7 = 3
    //!            a[3] = [[(a[0] % m + a[1]) % m + a[2]] % m + a[3]] % m = 3
    //!            max = max[(a[0] % m + a[1]) % m = 6,
    //!                     [[(a[0] % m + a[1]) % m + a[2]] % m + a[3]] % m = 3]
    //!                = 6
    //!     i = 4: sum = [[[(a[0] % m + a[1]) % m + a[2]] % m + a[3]] % m
    //!                + a[4]] % m = (3 + 5) % 7 = 1
    //!            a[4] = sum = 1
    //!            max = max(6, 1) = 6
    //! So a = [3, 6, 1, 3, 1] and max = 6
    for (auto& ele : a)
    {
        sum = (sum + ele) % m;
        ele = sum;
        max = std::max(max, sum);
    }
    
    //! The above code determines modulos for sums over a[0:n] but we also need
    //! to figure out modulos for sums over a[i:j]. If larger index j has a
    //! smaller prefix sum than any smaller index i then the sub-array (i, j]
    //! can be the solution if its sum % m is the maximum value.
    //! For example,
    //!            i = 0, 1, 2, 3
    //!         a[i] = 3, 2, 7, 4 and m = 7
    //!    prefix[i] = 3, 5, 5, 2
    //!
    //! where prefix[i = 0] > prefix[j = 3]. The sub-array (0, 3] is a potential
    //! solution. To get from prefix[i = 0] = 3 to prefix[j = 3] = 2, the value
    //! of 6 or 6 plus a multiple of 7 had to be added within the sub-array.
    //! So when the sum of this sub-array has modulo taken by 7, can get max.
    //!         a[i = 0] = 3
    //!                    3 + [2 + 7 + 4] = 3 + [13] -> 16
    //!                    16 % 7 = 2 = a[j = 3]
    //!    prefix[i = 0] = 3 -> prefix[j = 3] = 2
    //! prefix[i = 0] = 3; 3 + (6 + 0)  = 9;   9 % 7 = 2 = prefix[j = 3] or
    //! prefix[i = 0] = 3; 3 + (6 + 7)  = 16; 16 % 7 = 2 = prefix[j = 3] or
    //! prefix[i = 0] = 3; 3 + (6 + 14) = 23; 23 % 7 = 2 = prefix[j = 3], etc.
    //!
    //! If the prefix array is sorted (using a set), just need to find the min
    //! difference between all prefix sums where first index > second index.
    //! Since the prefix set is in increasing order, the first index will be j.
    //! Subtract this min difference from m to get the answer. e.g.
    //!            i = 3, 0, 1, 2
    //!         a[i] = 4, 3, 2, 7 and m = 7
    //!    prefix[i] = 2, 3, 5, 5
    //! where j = 3 > i = 0, prefix[i = 0] - prefix[j = 3] = 3 - 2 = 1
    //! and m - 1 = 7 - 1 = 6
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