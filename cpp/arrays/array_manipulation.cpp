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
    //! @details Time complexity O(n * m) and space complexity O(n)
    //!          n = Number of elements in array
    //!          m = Number of operations in queries
    //!          For each of m operations, takes O(n) time to process

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

//! @brief Solution from discussion section of HR
//! @param[in] n Number of elements in array
//! @param[in] queries Two dimensional vector of queries
//! @return Maximum value in resultant vector
static long arrayManipulationDiscussionSolution(
    int                           n,
    std::vector<std::vector<int>> queries)
{
    //! @details Time complexity O(n + m) and space complexity O(n)
    //!          n = Number of elements in array
    //!          m = Number of operations in queries
    //!          Process each operation in O(1) time - keep track of endpoints
    //!          instead of O(n) numbers between endpoints to decrease runtime.
    //!          So time complexity is O(n) for evaluation of max and O(m) for
    //!          operations described previously

    //! Vector to store n + 1 elements
    std::vector<long> ele_vec(n + 1);
    
    //! Loop over operation vectors
    for (const auto& op_vec : queries)
    {
        //! Get start/end indices
        const auto a = static_cast<std::size_t>(op_vec.front());
        const auto b = static_cast<std::size_t>(op_vec[1]);
        
        //! Value to add/subtract from elements in ele_vec
        const auto k = static_cast<long>(op_vec.back());
        
        //! To distinguish between left endpoint a and right endpoint b, store
        //! +k for the former and -k for the latter.
        //! We have stored info from m operations in O(m) time
        ele_vec[a - 1ULL] += k;
        ele_vec[b]        -= k;
    }
    
    //! Find max value
    long sum {};
    long max {};

    //! Traverse vector from left to right
    //! Whenever reach left endpoint a, add +k to sum
    //! Whenever reach right endpoint b, add -k to sum
    for (int i = 0; i < n; ++i)
    {
        sum += ele_vec[i];
        max =  std::max(max, sum);
    }

    return max;

} // static long arrayManipulationDiscussionSolution( ...

// Test case 0
TEST(ArrayManipulationTest, TestCase0) {
    std::vector<std::vector<int>> queries {
        {1, 2, 100},
        {2, 5, 100},
        {3, 4, 100}};

    EXPECT_EQ(200L, arrayManipulationNaive(5, queries));
    EXPECT_EQ(200L, arrayManipulationDiscussionSolution(5, queries));

    //! Step-through of logic
    //! 1-based:   1   2   3   4   5
    //! Indices:   0   1   2   3   4
    //! Query 1: 100 100   0   0   0
    //! Query 2: 100 200 100 100 100
    //! Query 3: 100 200 200 200 100

    //! Explanation of discussion solution:
    //! For query 1, arr[0] and every element to the right will have 100 added
    //! to it. arr[2] and every element to the right will have -100 added to it
    
    //! 1-based:    1    2    3    4    5    6
    //! Indices:    0    1    2    3    4    5
    //! ele_vec:  100    0 -100    0    0    0
    //! sum[0] = 0 + 100       = 100
    //! sum[1] = 0 + 100       = 100
    //! sum[2] = 0 + 100 - 100 = 0
    //! sum[3] = 0 + 100 - 100 = 0
    //! sum[4] = 0 + 100 - 100 = 0
    //! sum[5] = 0 + 100 - 100 = 0
    //! So Query 1: [100, 100, 0, 0, 0, 0]

    //! 1-based:    1    2    3    4    5    6
    //! Indices:    0    1    2    3    4    5
    //! ele_vec:  100  100 -100    0    0 -100
    //! sum[0] = 0 + 100                   = 100
    //! sum[1] = 0 + 100 + 100             = 200
    //! sum[2] = 0 + 100 + 100 - 100       = 100
    //! sum[3] = 0 + 100 + 100 - 100       = 100
    //! sum[4] = 0 + 100 + 100 - 100       = 100
    //! sum[5] = 0 + 100 + 100 - 100 - 100 = 0
    //! So Query 2: [100, 200, 100, 100, 100, 0]

    //! 1-based:    1    2    3    4    5    6
    //! Indices:    0    1    2    3    4    5
    //! ele_vec:  100  100    0    0 -100 -100
    //! sum[0] = 0 + 100                   = 100
    //! sum[1] = 0 + 100 + 100             = 200
    //! sum[2] = 0 + 100 + 100             = 200
    //! sum[3] = 0 + 100 + 100             = 200
    //! sum[4] = 0 + 100 + 100 - 100       = 100
    //! sum[5] = 0 + 100 + 100 - 100 - 100 = 0
    //! So Query 3: [100, 200, 200, 200, 100, 0]
}

// Test case 14
TEST(ArrayManipulationTest, TestCase14) {
    std::vector<std::vector<int>> queries {
        {1, 5, 3},
        {4, 8, 7},
        {6, 9, 1}};

    EXPECT_EQ(10L, arrayManipulationNaive(10, queries));
    EXPECT_EQ(10L, arrayManipulationDiscussionSolution(10, queries));
}

// Test case 15
TEST(ArrayManipulationTest, TestCase15) {
    std::vector<std::vector<int>> queries {
        {2, 6, 8},
        {3, 5, 7},
        {1, 8, 1},
        {5, 9, 15}};

    EXPECT_EQ(31L, arrayManipulationNaive(10, queries));
    EXPECT_EQ(31L, arrayManipulationDiscussionSolution(10, queries));
}