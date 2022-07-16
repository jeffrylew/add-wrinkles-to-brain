#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Implementation of counting sort
//! @param[in] unsorted_vec Vector of unsorted ints passed by value
//! @param[in] k            Maximum key value as an int
//! @pre Integer keys in unsorted_vec are non-negative
//! @return Vector of sorted ints
static std::vector<int> countingSort(std::vector<int> unsorted_vec, int k)
{
    // Auxiliary vector storing count of element at index i
    // "+ 1" accounts for element 0 (i = 0)
    // "k" is the last index in count_vec
    std::vector<int> count_vec(static_cast<std::size_t>(k + 1));

    // Output vector of sorted elements
    std::vector<int> sorted_vec(unsorted_vec.size());

    // Populate count_vec with histogram of elements in unsorted_vec
    for (std::size_t i = 0; i < unsorted_vec.size(); ++i)
    {
        // Element value is index into count_vec
        const auto count_idx = static_cast<std::size_t>(unsorted_vec.at(i));

        // Increment count of element seen at i
        ++count_vec.at(count_idx);
    }

    // Perform prefix sum computation on count to determine position range
    for (std::size_t i = 1ULL; i <= static_cast<std::size_t>(k); i++)
    {
        count_vec.at(i) += count_vec.at(i - 1);
    }
    
    // Reverse iterate over unsorted_vec and place elements in correct positions
    // Use int for index since it will be decremented below zero
    for (int i = static_cast<int>(unsorted_vec.size()) - 1; i >= 0; --i)
    {
        const auto unsorted_at_i = unsorted_vec.at(static_cast<std::size_t>(i));

        // Element value is index into count_vec
        const auto count_idx = static_cast<std::size_t>(unsorted_at_i);

        // count_vec[count_idx] - 1 is location of element i in sorted array
        const auto idx_in_sorted_vec =
            static_cast<std::size_t>(--count_vec.at(count_idx));
        
        // Copy element from unsorted_vec to sorted_vec at idx_in_sorted_vec
        sorted_vec.at(idx_in_sorted_vec) = unsorted_at_i;
    }
    
    return sorted_vec;

} // static std::vector<int> countingSort( ...

// Try some basic cases
TEST(CountingSortTest, BasicCases) {
    auto sorted_vec = countingSort({1}, 1);
    EXPECT_TRUE(std::is_sorted(sorted_vec.cbegin(), sorted_vec.cend()));

    sorted_vec = countingSort({2, 1}, 2);
    EXPECT_TRUE(std::is_sorted(sorted_vec.cbegin(), sorted_vec.cend()));

    sorted_vec = countingSort({3, 2, 1}, 3);
    EXPECT_TRUE(std::is_sorted(sorted_vec.cbegin(), sorted_vec.cend()));
}

// Try sorting a random vector of ints
TEST(CountingSortTest, RandomCase) {
    auto sorted_vec = countingSort({4, 2, 1, 5, 3}, 5);
    EXPECT_TRUE(std::is_sorted(sorted_vec.cbegin(), sorted_vec.cend()));
}