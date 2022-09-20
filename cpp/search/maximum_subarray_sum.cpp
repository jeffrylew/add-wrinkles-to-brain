#include <gtest/gtest.h>

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

// Test case 0
TEST(MaximumSumTest, TestCase0) {
    EXPECT_EQ(6L, maximumSumFirstAttempt({3L, 3L, 9L, 9L, 5L}, 7L));
}

// Test case 17
TEST(MaximumSumTest, TestCase17) {
    EXPECT_EQ(1L, maximumSumFirstAttempt({1L, 2L, 3L}, 2L));
}

// Test case 18
TEST(MaximumSumTest, TestCase18) {
    EXPECT_EQ(4L, maximumSumFirstAttempt({1L, 5L, 9L}, 5L));
}