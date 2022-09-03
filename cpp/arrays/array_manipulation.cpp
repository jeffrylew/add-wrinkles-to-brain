#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief First attempt naive solution times out for Test cases 7-13
//! @param[in] n Number of elements in array
//! @param[in] queries Two dimensional vector of queries
//! @return Maximum value in resultant vector
static long arrayManipulationNaive(int                           n,
                                   std::vector<std::vector<int>> queries)
{
    //! Vector to store elements
    std::vector<long> ele_vec(n);
    
    //! Loop over operation vectors
    for (const auto& op_vec : queries)
    {
        //! Get start/end indices, make them 0-based
        const auto start_idx = static_cast<std::size_t>(op_vec.front() - 1);
        const auto end_idx   = static_cast<std::size_t>(op_vec[1] - 1);
        
        //! Value to add to elements in ele_vec
        const auto to_add = static_cast<long>(op_vec.back());
        
        for (std::size_t i = start_idx; i <= end_idx; ++i)
        {
            ele_vec[i] += to_add;
        }
    }
    
    return *std::max_element(ele_vec.cbegin(), ele_vec.cend());

} // static long arrayManipulationNaive( ...

// Test case 0
TEST(ArrayManipulationTest, TestCase0) {
    std::vector<std::vector<int>> queries {
        {1, 2, 100},
        {2, 5, 100},
        {3, 4, 100}};

    EXPECT_EQ(200L, arrayManipulationNaive(5, queries));
}

// Test case 14
TEST(ArrayManipulationTest, TestCase14) {
    std::vector<std::vector<int>> queries {
        {1, 5, 3},
        {4, 8, 7},
        {6, 9, 1}};

    EXPECT_EQ(10L, arrayManipulationNaive(10, queries));
}

// Test case 15
TEST(ArrayManipulationTest, TestCase15) {
    std::vector<std::vector<int>> queries {
        {2, 6, 8},
        {3, 5, 7},
        {1, 8, 1},
        {5, 9, 15}};

    EXPECT_EQ(31L, arrayManipulationNaive(10, queries));
}