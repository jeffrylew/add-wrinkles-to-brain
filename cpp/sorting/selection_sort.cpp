#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Get index of smallest value in vector
//! @param[in] arr Vector of unsorted ints passed by value
//! @return Index of smallest value in vector as size_t
static std::size_t findSmallestIdx(std::vector<int> arr)
{
    // Stores smallest value
    auto smallest_val = arr.front();

    // Stores index of the smallest value
    std::size_t smallest_idx {0ULL};

    for (std::size_t i = 1ULL; i < arr.size(); ++i)
    {
        if (arr.at(i) < smallest_val)
        {
            smallest_val = arr.at(i);
            smallest_idx = i;
        }
    }
    return smallest_idx;

} // static std::size_t findSmallestIdx( ...

//! @brief Selection sort from grokking algorithms
//! @param[in] arr Vector of unsorted ints passed by value
//! @return Vector of sorted ints
static std::vector<int> selectionSortGrokkingAlgs(std::vector<int> arr)
{
    std::vector<int> sorted_arr {};
    sorted_arr.reserve(arr.size());

    for (std::size_t i = 0ULL; i < arr.size(); ++i)
    {
        // Don't use index since harder to erase from vector
        // auto smallest_idx = findSmallestIdx(arr);

        // Get iterator to smallest element in vector instead
        auto smallest_it = std::min_element(arr.begin(), arr.end());

        if (smallest_it != arr.end())
        {
            // Add to sorted_arr
            sorted_arr.emplace_back(*smallest_it);

            // Remove smallest element from arr
            arr.erase(smallest_it);
        }
    }
    
    return sorted_arr;

} // static std::vector<int> selectionSortGrokkingAlgs( ...

// Try when input is already sorted
TEST(SelectionSortTest, SortedTestCase) {
    std::vector<int> arr {1, 2, 3, 4, 5};

    auto sorted_arr = selectionSortGrokkingAlgs(arr);
    EXPECT_TRUE(std::is_sorted(sorted_arr.cbegin(), sorted_arr.cend()));
}

// Try when input is not sorted
TEST(SelectionSortTest, UnsortedTestCase) {
    std::vector<int> arr {5, 4, 3, 2, 1};

    auto sorted_arr = selectionSortGrokkingAlgs(arr);
    EXPECT_TRUE(std::is_sorted(sorted_arr.cbegin(), sorted_arr.cend()));
}