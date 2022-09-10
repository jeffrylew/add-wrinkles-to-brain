#include <gtest/gtest.h>

#include <vector>

//! @brief First attempt solution
//! @param[in] graph_nodes Number of nodes
//! @param[in] graph_from  Vector of start nodes for each edge
//! @param[in] graph_to    Vector of end nodes for each edge
//! @param[in] ids         Color id per node
//! @param[in] val         Color id to match
//! @return Length of shortest path between two nodes of same color, else -1
static int findShortestFirstAttempt(int               graph_nodes,
                                    std::vector<int>  graph_from,
                                    std::vector<int>  graph_to,
                                    std::vector<long> ids,
                                    int               val)
{
    

} // static int findShortestFirstAttempt( ...

// Test case 0
TEST(FindShortestTest, TestCase0) {
    EXPECT_EQ(1, findShortestFirstAttempt(4,
                                          {1, 1, 4},
                                          {2, 3, 2},
                                          {1L, 2L, 1L, 1L},
                                          1));
}

// Test case 1
TEST(FindShortestTest, TestCase1) {
    EXPECT_EQ(-1, findShortestFirstAttempt(4,
                                           {1, 1, 4},
                                           {2, 3, 2},
                                           {1L, 2L, 3L, 4L},
                                           2));
}

// Test case 2
TEST(FindShortestTest, TestCase2) {
    EXPECT_EQ(3, findShortestFirstAttempt(5,
                                          {1, 1, 2, 3},
                                          {2, 3, 4, 5},
                                          {1L, 2L, 3L, 3L, 2L},
                                          2));
}