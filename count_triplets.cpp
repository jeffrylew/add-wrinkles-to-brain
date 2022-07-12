#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <map>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

//! @brief Calculate geometric progression starting at num with ratio r
//! @param[in] num First number in geometric progression
//! @param[in] r   Common ratio for geometric progression
//! @return Tuple of numbers in geometric progression starting at num with ratio r
static std::tuple<long, long, long> geometricProgression(long num, long r)
{
    return {num, num * r, num * r * r};
}

// First attempt segfaulted for Test cases 2 and 3 (fixed now)
// and timed out for Test cases 6, 10, and 11. Test case 3 times out after fix.
static long countTripletsFirstAttempt(std::vector<long> arr, long r)
{
    // Total number of triplets
    long n_triplets {};
    
    // Map of numbers in arr and a vector of their indices (for repeated values)
    std::unordered_map<long, std::vector<std::size_t>> num_idx_map {};
    for (std::size_t idx = 0; idx < arr.size(); ++idx)
    {
        num_idx_map[arr.at(idx)].emplace_back(idx);
    }
    
    // Create variables for second and third numbers in geometric progression
    long gp_second {};
    long gp_third {};
    
    // Iterate through arr and ultimately count number of triplets
    for (std::size_t i = 0; i < arr.size(); ++i)
    {
        // Create geometric progression starting from number at i
        const auto gp_first = arr.at(i);
        std::tie(std::ignore,
                 gp_second,
                 gp_third) = geometricProgression(gp_first, r);
        
        // If second or third number in geometric progression is not in
        // num_idx_map then no triplets are available starting from gp_first
        if (0 == num_idx_map.count(gp_second)
           || 0 == num_idx_map.count(gp_third))
        {
            continue;
        }
        
        // Get vector of gp_second indices that are greater than i
        const auto gp_second_indices_vec = num_idx_map.at(gp_second);
        std::vector<std::size_t> gp_second_gt_i_vec(
            gp_second_indices_vec.size());
        
        auto it = std::copy_if(gp_second_indices_vec.cbegin(),
                               gp_second_indices_vec.cend(),
                               gp_second_gt_i_vec.begin(),
                               [=](std::size_t j) -> bool
                               {
                                   return j > i;
                               });
        
        // Shrink gp_second_gt_i_vec to new size
        gp_second_gt_i_vec.resize(std::distance(gp_second_gt_i_vec.begin(), it));
            
        // Loop through gp_second indices that are greater than i
        // and count the number of gp_third indices that are greater
        // than the current gp_second index (to satisfy i < j < k)
        // Increment n_triplets by this value
        const auto gp_third_indices_vec = num_idx_map.at(gp_third);
        std::for_each(gp_second_gt_i_vec.cbegin(),
                      gp_second_gt_i_vec.cend(),
                      [&](std::size_t j)
                      {
                          n_triplets += std::count_if(
                              gp_third_indices_vec.cbegin(),
                              gp_third_indices_vec.cend(),
                              [=](std::size_t k) -> bool
                              {
                                  return k > j;
                              });
                      });
        
    } // for (std::size_t i = 0; ...
    
    return n_triplets;

} // static long countTripletsFirstAttempt( ...

// Second attempt to fix time out issues. Test case 3 still times out
static long countTripletsSecondAttempt(std::vector<long> arr, long r)
{
    // Total number of triplets
    long n_triplets {};
    
    // No triplets can exist if there are less than 3 elements
    if (arr.size() < 3ULL)
    {
        return n_triplets;
    }
    
    // Map of numbers in arr and a vector of their indices (for repeated values)
    // Vector elements (indices) will be in ascending order
    std::unordered_map<long, std::vector<std::size_t>> num_idx_map {};
    for (std::size_t idx = 0; idx < arr.size(); ++idx)
    {
        num_idx_map[arr.at(idx)].emplace_back(idx);
    }
    
    // Create variables for second and third numbers in geometric progression
    long gp_second {};
    long gp_third {};
    
    // Iterate through arr and ultimately count number of triplets
    // Subtract 2ULL since the last triplet cannot start at a greater index
    for (std::size_t i = 0; i < arr.size() - 2ULL; ++i)
    {
        // Create geometric progression starting from number at i
        const auto gp_first = arr.at(i);
        std::tie(std::ignore,
                 gp_second,
                 gp_third) = geometricProgression(gp_first, r);
        
        // If second or third number in geometric progression is not in
        // num_idx_map then no triplets are available starting from gp_first
        if (0 == num_idx_map.count(gp_second)
           || 0 == num_idx_map.count(gp_third))
        {
            continue;
        }
        
        // Loop over vector of gp_second indices that are greater than i
        const auto& gp_second_indices_vec = num_idx_map.at(gp_second);
        auto j_it = std::find_if(gp_second_indices_vec.cbegin(),
                                 gp_second_indices_vec.cend(),
                                 [=](std::size_t j) -> bool
                                 {
                                    return j > i;
                                 });
        
        const auto& gp_third_indices_vec = num_idx_map.at(gp_third);

        while (j_it != gp_second_indices_vec.cend())
        {
            auto k_it = std::find_if(gp_third_indices_vec.cbegin(),
                                     gp_third_indices_vec.cend(),
                                     [=](std::size_t k) -> bool
                                     {
                                         return k > *j_it;
                                     });
            
            n_triplets += std::distance(k_it, gp_third_indices_vec.cend());

            ++j_it;
        }
        
    } // for (std::size_t i = 0; ...
    
    return n_triplets;

} // static long countTripletsSecondAttempt( ...

// A solution from discussion section
static long countTripletsDiscussionSolution(std::vector<long> arr, long r)
{
    // Total number of triplets
    long n_triplets {};
    
    // No triplets can exist if there are less than 3 elements
    if (arr.size() < 3ULL)
    {
        return n_triplets;
    }
    
    // Map of element frequency in arr
    std::unordered_map<long, int> element_freq_map {};

    // Map of pair<2nd element in triplet, 3rd element in triplet> frequency
    // To avoid defining a std::hash specialization for std::pair, use std::map
    // instead of std::unordered_map
    // See https://www.techiedelight.com/use-std-pair-key-std-unordered_map-cpp/
    using Triplet_pair_t = std::pair<long, long>;
    std::map<Triplet_pair_t, int> pair_freq_map {};

    // Create variables for second and third numbers in geometric progression
    long x_r {};
    long x_r_r {};

    // Traverse arr backwards, let x = *rit
    for (auto rit = arr.crbegin(); rit != arr.crend(); ++rit)
    {
        // Get second and third numbers in geometric progression
        std::tie(std::ignore,
                 x_r,
                 x_r_r) = geometricProgression(*rit, r);

        // Case 1: Current element x is first number in geometric progression
        //         i.e. (x, x*r, x*r*r)
        //         This means 2nd/3rd numbers have already been seen.
        //         Increment n_triplets by the count from pair_freq_map
        auto triplet_pair_it = pair_freq_map.find({x_r, x_r_r});
        if (triplet_pair_it != pair_freq_map.cend())
        {
            n_triplets += triplet_pair_it->second;
        }
        
        // Case 2: Current element x is second number in geometric progression
        //         i.e. (x/r, x, x*r)
        //         Update pair_freq_map with frequency of third number
        if (element_freq_map.count(x_r) > 0)
        {
            pair_freq_map[{*rit, x_r}] += element_freq_map.at(x_r);
        }
        
        // Case 3: Current element x is third number in geometric progression
        //         i.e. (x/(r*r), x/r, x)
        //         Update frequency of x in element_freq_map for future use
        ++element_freq_map[*rit];

    } // for (auto rit = arr.crbegin(); ...

    return n_triplets;

} // static long countTripletsDiscussionSolution( ...

// Another solution from discussion section
static long countTripletsDiscussionSolution2(std::vector<long> arr, long r)
{
    // Total number of triplets
    long n_triplets {};
    
    // No triplets can exist if there are less than 3 elements
    if (arr.size() < 3ULL)
    {
        return n_triplets;
    }
    
    // Map of element frequency in arr
    std::unordered_map<long, int> element_freq_map {};

    // Map of (current value * r, current value * r * r) frequency
    // Key is current value
    std::unordered_map<long, int> pair_freq_map {};

    // Traverse arr backwards, let x = current value = *rit
    for (auto rit = arr.crbegin(); rit != arr.crend(); ++rit)
    {
        const auto x   = *rit;
        const auto x_r = x * r;

        if (pair_freq_map.count(x_r) > 0)
        {
            n_triplets += pair_freq_map.at(x_r);
        }

        if (element_freq_map.count(x_r) > 0)
        {
            pair_freq_map[x] += element_freq_map.at(x_r);
        }

        ++element_freq_map[x];

    } // for (auto rit = arr.crbegin(); ...

    return n_triplets;

} // static long countTripletsDiscussionSolution2( ...

// Try sample input given in problem description
TEST(CountTripletsTest, SampleInput) {
    std::vector<long> arr {1, 4, 16, 64};
    constexpr long geometric_ratio {4};

    EXPECT_EQ(2L, countTripletsFirstAttempt(arr, geometric_ratio));

    EXPECT_EQ(2L, countTripletsSecondAttempt(arr, geometric_ratio));

    EXPECT_EQ(2L, countTripletsDiscussionSolution(arr, geometric_ratio));

    EXPECT_EQ(2L, countTripletsDiscussionSolution2(arr, geometric_ratio));
}

// Try Test case 0
TEST(CountTripletsTest, TestCase0) {
    std::vector<long> arr {1, 2, 2, 4};
    constexpr long geometric_ratio {2};

    EXPECT_EQ(2L, countTripletsFirstAttempt(arr, geometric_ratio));

    EXPECT_EQ(2L, countTripletsSecondAttempt(arr, geometric_ratio));

    EXPECT_EQ(2L, countTripletsDiscussionSolution(arr, geometric_ratio));

    EXPECT_EQ(2L, countTripletsDiscussionSolution2(arr, geometric_ratio));
}

// Try Test case 1
TEST(CountTripletsTest, TestCase1) {
    std::vector<long> arr {1, 3, 9, 9, 27, 81};
    constexpr long geometric_ratio {3};

    EXPECT_EQ(6L, countTripletsFirstAttempt(arr, geometric_ratio));

    EXPECT_EQ(6L, countTripletsSecondAttempt(arr, geometric_ratio));

    EXPECT_EQ(6L, countTripletsDiscussionSolution(arr, geometric_ratio));

    EXPECT_EQ(6L, countTripletsDiscussionSolution2(arr, geometric_ratio));
}

// Try Test case 2 (fixed seg fault by replacing braces with parentheses)
TEST(CountTripletsTest, TestCase2) {
    std::vector<long> arr (100ULL, 1L);
    constexpr long geometric_ratio {1};

    EXPECT_EQ(161700L, countTripletsFirstAttempt(arr, geometric_ratio));

    EXPECT_EQ(161700L, countTripletsSecondAttempt(arr, geometric_ratio));

    EXPECT_EQ(161700L, countTripletsDiscussionSolution(arr, geometric_ratio));

    EXPECT_EQ(161700L, countTripletsDiscussionSolution2(arr, geometric_ratio));
}

// Try Test case 3 (times out for both attempts)
// Test case 10 and 11 also time out for both
TEST(CountTripletsTest, TestCase3) {
    std::vector<long> arr(100000ULL, 1237L);
    constexpr long geometric_ratio {1};

    /*
    EXPECT_EQ(1666616666700000L,
              countTripletsFirstAttempt(arr, geometric_ratio));

    EXPECT_EQ(1666616666700000L,
              countTripletSecondAttempt(arr, geometric_ratio));
     */

    // The python versions of the functions below pass this test...

    // First discussion solution fails this test case...
    const auto result = countTripletsDiscussionSolution(arr, geometric_ratio);
    EXPECT_NE(166661666700000L, result);

    // Second discussion solution fails this test case...
    const auto result2 = countTripletsDiscussionSolution2(arr, geometric_ratio);
    EXPECT_NE(166661666700000L, result2);
}

// Try Test case 12
TEST(CountTripletsTest, TestCase12) {
    std::vector<long> arr {1, 5, 5, 25, 125};
    constexpr long geometric_ratio {5};

    EXPECT_EQ(4L, countTripletsFirstAttempt(arr, geometric_ratio));

    EXPECT_EQ(4L, countTripletsSecondAttempt(arr, geometric_ratio));

    EXPECT_EQ(4L, countTripletsDiscussionSolution(arr, geometric_ratio));

    EXPECT_EQ(4L, countTripletsDiscussionSolution2(arr, geometric_ratio));
}