#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <tuple>
#include <unordered_set>
#include <vector>

static int pairs(int k, std::vector<int> arr)
{
    // Total number of pairs that have desired difference
    int n_pairs {};
    
    // Descending sort
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    
    // Set to hold second value in difference of k
    std::unordered_set<int> second_vals {};
    
    // Loop over first values in difference of k
    for (const auto first_val : arr)
    {
        // Add first value to second_vals set
        auto ret = second_vals.emplace(first_val);
        
        // If first value could not be added, it satisfies
        // the difference as a second value for a larger int
        if (not ret.second)
        {
            ++n_pairs;
        }
        
        // Add its desired second value to second_vals
        // Since vector is sorted in descending order,
        // this second value will not exist in second_vals
        std::ignore = second_vals.emplace(first_val - k);
    }
    
    return n_pairs;

} // static int pairs( ...

//! @brief Discussion solution
//! @param[in] k   Target difference as an int
//! @param[in] arr Vector of integers
//! @return Number of pairs that satisfy the difference criterion
static int pairsDiscussionSolution(int k, std::vector<int> arr)
{
    // Ascending sort
    std::sort(arr.begin(), arr.end());

    // Total number of pairs that have desired difference
    int n_pairs {};

    // Variables for two pointer approach
    std::size_t i {};
    std::size_t j {1ULL};

    while (j < arr.size())
    {
        const auto diff = arr.at(j) - arr.at(i);

        if (diff == k)
        {
            ++n_pairs;
            ++j;
        }
        else if (diff > k)
        {
            ++i;
        }
        else if (diff < k)
        {
            ++j;
        }

    } // while (j < arr.size())

    return n_pairs;

} // static int pairsDiscussionSolution( ...

//! @brief Editorial solution
//! @param[in] k   Target difference as an int
//! @param[in] arr Vector of integers
//! @return Number of pairs that satisfy the difference criterion
static int pairsEditorialSolution(int k, std::vector<int> arr)
{
    // Total number of pairs that have desired difference
    int n_pairs {};

    std::unordered_set<int> s {};

    // Add values into set
    for (const auto val : arr)
    {
        std::ignore = s.emplace(val);
    }

    for (const auto val : s)
    {
        if (s.count(val + k) > 0)
        {
            ++n_pairs;
        }
    }

    return n_pairs;

} // static int pairsEditorialSolution( ...

// Try sample input given in problem description
TEST(PairsTest, SampleInput) {
    EXPECT_EQ(3, pairs(1, {1, 2, 3, 4}));
    EXPECT_EQ(3, pairsDiscussionSolution(1, {1, 2, 3, 4}));
    EXPECT_EQ(3, pairsEditorialSolution(1, {1, 2, 3, 4}));
}

// Test case 15
TEST(PairsTest, TestCase15) {
    EXPECT_EQ(3, pairs(2, {1, 5, 3, 4, 2}));
    EXPECT_EQ(3, pairsDiscussionSolution(2, {1, 5, 3, 4, 2}));
    EXPECT_EQ(3, pairsEditorialSolution(2, {1, 5, 3, 4, 2}));
}

// Test case 16
TEST(PairsTest, TestCase16) {
    const std::vector<int> arr {
        363374326,
        364147530,
        61825163,
        1073065718,
        1281246024,
        1399469912,
        428047635,
        491595254,
        879792181,
        1069262793};

    EXPECT_EQ(0, pairs(1, arr));
    EXPECT_EQ(0, pairsDiscussionSolution(1, arr));
    EXPECT_EQ(0, pairsEditorialSolution(1, arr));
}

// Test case 17
TEST(PairsTest, TestCase17) {
    EXPECT_EQ(5, pairs(2, {1, 3, 5, 8, 6, 4, 2}));
    EXPECT_EQ(5, pairsDiscussionSolution(2, {1, 3, 5, 8, 6, 4, 2}));
    EXPECT_EQ(5, pairsEditorialSolution(2, {1, 3, 5, 8, 6, 4, 2}));
}