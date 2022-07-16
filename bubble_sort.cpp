#include <gtest/gtest.h>

#include <algorithm>
#include <tuple>
#include <vector>

//! @brief Count the number of swaps made using bubble sort
//! @param[in] a Vector of ints passed by value
//! @return std::tuple of number of swaps, first element, and last element
static std::tuple<int, int, int> countSwaps(std::vector<int> a)
{
    // Number of swaps
    int numSwaps {};
    
    // a is guaranteed to have at least two elements
    const auto a_size = a.size();
    
    for (std::size_t i = 0; i < a_size; ++i)
    {
        for (std::size_t j = 0; j < a_size - 1; ++j)
        {
            // Swap adjacent elements if they are in decreasing order
            if (a.at(j) > a.at(j + 1))
            {
                std::swap(a.at(j), a.at(j + 1));
                ++numSwaps;
            }
        }
    }
    
    return {numSwaps, a.front(), a.back()};

} // static std::tuple<int, int, int> countSwaps( ...

// Try Test case 0
TEST(BubbleSortTest, TestCase0) {
    std::vector<int> a {1, 2, 3};

    const auto ret = countSwaps(a);
    EXPECT_EQ(0, std::get<0>(ret));
    EXPECT_EQ(1, std::get<1>(ret));
    EXPECT_EQ(3, std::get<2>(ret));
}

// Try Test case 1
TEST(BubbleSortTest, TestCase1) {
    std::vector<int> a {3, 2, 1};

    const auto ret = countSwaps(a);
    EXPECT_EQ(3, std::get<0>(ret));
    EXPECT_EQ(1, std::get<1>(ret));
    EXPECT_EQ(3, std::get<2>(ret));
}

// Try Test case 3
TEST(BubbleSortTest, TestCase3) {
    std::vector<int> a {4, 2, 3, 1};

    const auto ret = countSwaps(a);
    EXPECT_EQ(5, std::get<0>(ret));
    EXPECT_EQ(1, std::get<1>(ret));
    EXPECT_EQ(4, std::get<2>(ret));
}