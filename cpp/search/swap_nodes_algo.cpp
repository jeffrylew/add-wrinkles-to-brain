#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <map>
#include <utility>
#include <vector>

static std::vector<std::vector<int>> swapNodesFirstAttempt(
    std::vector<std::vector<int>> indexes,
    std::vector<int>              queries)
{
    // If indexes is empty, root node will be only node in tree
    // Or if indexes only has one vector filled with -1s, root is only node
    // In-order traversal will return same tree no matter how many swaps
    if (indexes.empty()
        || (1ULL == indexes.size()
            && -1 == indexes.front().front()
            && -1 == indexes.front().back()))
    {
        return {{1}};
    }
    
    // Map of key = depth, value = Vector of left/child nodes of node from depth
    std::map<int, std::vector<std::vector<int>>> child_nodes_from_depth {};
    
    // From now on, tree has at least depth 2
    int h_curr {1};
    
    // Part I: Fill child_nodes_from_depth
    
    // Add root's (depth = 1) children to child_nodes_from_depth
    child_nodes_from_depth[h_curr].emplace_back(indexes.front());
    
    while (not child_nodes_from_depth[h_curr].empty())
    {
        // Loop over child node(s) of node at depth
        for (std::size_t i = 0;
             i < child_nodes_from_depth.at(h_curr).size();
             ++i)
        {
            // Get indices of left and right children of current child_vec
            const auto& child_vec = child_nodes_from_depth.at(h_curr).at(i);

            const auto left_child_idx  = std::max(-1, child_vec.front() - 1);
            const auto right_child_idx = std::max(-1, child_vec.back() - 1);
            
            // Add the children of child_vec to child_nodes_at_depth
            // at the next depth
            if (-1 != left_child_idx)
            {
                child_nodes_from_depth[1 + h_curr].emplace_back(
                    indexes.at(left_child_idx));
            }
            if (-1 != right_child_idx)
            {
                child_nodes_from_depth[1 + h_curr].emplace_back(
                    indexes.at(right_child_idx));
            }
            
        } // for (std::size_t i = 0; ...
        
        // Increment h_curr to process children at next depth
        ++h_curr;
        
    } // while (not child_nodes_from_depth[h_curr].empty())
    
    // Part II: Perform swaps from queries
    for (const auto k : queries)
    {
        for (auto& kv : child_nodes_from_depth)
        {
            const auto depth          = kv.first;
            auto&      child_node_vec = kv.second;
            
            if (0 != depth % k)
            {
                // Depth is not a multiple of k so don't swap subtrees
                continue;
            }
            
            if (child_node_vec.empty())
            {
                // Skip if no child nodes in vector
                continue;
            }
            
            // Swap children of node from depth
            for (auto& left_right_vec : child_node_vec)
            {
                std::swap(left_right_vec.front(),
                          left_right_vec.back());
            }
            
        } // for (auto& kv : child_nodes_from_depth)
        
    } // for (const auto k : queries)
    
    // Part III: Perform inorder traversal of nodes
    
    // Output vector to hold inorder traversal of nodes
    std::vector<std::vector<int>> inorder_traversal(queries.size());
    
    // TODO: How to convert child_nodes_from_depth map
    //       (level order traversal) to inorder traversal?
    
    return inorder_traversal;

} // static std::vector<std::vector<int>> swapNodesFirstAttempt( ...

// 1-based indexing, 0th index unused
constexpr std::size_t MAX_NODES {1024ULL + 1ULL};

//! @brief Calculate depth of current node and every child beneath it
//! @param[in]  curr_node      Index of current node (is also its value)
//! @param[in]  curr_depth     Depth of current node
//! @param[in]  left_children  Reference to left child nodes array
//! @param[in]  right_children Reference to right child nodes array
//! @param[out] depth_arr      Reference to array of node depths
static void calc_depth(std::size_t                       curr_node,
                       int                               curr_depth,
                       const std::array<int, MAX_NODES>& left_children,
                       const std::array<int, MAX_NODES>& right_children,
                       std::array<int, MAX_NODES>&       depth_arr)
{
    depth_arr.at(curr_node) = curr_depth;

    if (left_children.at(curr_node) > 0)
    {
        calc_depth(left_children.at(curr_node),
                   curr_depth + 1,
                   left_children,
                   right_children,
                   depth_arr);
    }
    
    if (right_children.at(curr_node) > 0)
    {
        calc_depth(right_children.at(curr_node),
                   curr_depth + 1,
                   left_children,
                   right_children,
                   depth_arr);
    }
    
} // static void calc_depth( ...

//! @brief Evaluate inorder traversal of tree
//! @param[in]  curr_node         Index of current node (is also its value)
//! @param[in]  left_chilren      Reference to left child nodes array
//! @param[in]  right_children    Reference to right child nodes array
//! @param[out] inorder_traversal Reference to vector storing inorder traversal
static void in_order(std::size_t                       curr_node,
                     const std::array<int, MAX_NODES>& left_children,
                     const std::array<int, MAX_NODES>& right_children,
                     std::vector<int>&                 inorder_traversal)
{
    if (left_children.at(curr_node) > 0)
    {
        in_order(left_children.at(curr_node),
                 left_children,
                 right_children,
                 inorder_traversal);
    }
    
    inorder_traversal.emplace_back(static_cast<int>(curr_node));

    if (right_children.at(curr_node) > 0)
    {
        in_order(right_children.at(curr_node),
                 left_children,
                 right_children,
                 inorder_traversal);
    }

} // static void in_order( ...

//! @brief Discussion solution from https://ideone.com/Fml7Sm
static std::vector<std::vector<int>> swapNodesDiscussionSolution(
    std::vector<std::vector<int>> indexes,
    std::vector<int>              queries)
{
    std::array<int, MAX_NODES> left_children {};
    std::array<int, MAX_NODES> right_children {};
    std::array<int, MAX_NODES> depth_arr {};

    // Populate left and right child arrays starting from those of node 1
    for (std::size_t i = 1; i <= indexes.size(); ++i)
    {
        left_children.at(i)  = indexes.at(i - 1ULL).front();
        right_children.at(i) = indexes.at(i - 1ULL).back();
    }
    
    // Fill depth_arr starting with node 1
    calc_depth(1, 1, left_children, right_children, depth_arr);

    // Output vector of inorder traversals
    std::vector<std::vector<int>> inorder_traversals {};

    // Perform swaps from queries
    for (const auto k : queries)
    {
        for (std::size_t i = 1; i <= indexes.size(); ++i)
        {
            if (0 == depth_arr.at(i) % k)
            {
                // Depth of node i is a multiple of k, swap its children
                std::swap(left_children.at(i), right_children.at(i));
            }
        }

        // Add to vector of inorder traversals
        std::vector<int> inorder_traversal {};
        in_order(1ULL, left_children, right_children, inorder_traversal);
        inorder_traversals.emplace_back(std::move(inorder_traversal));
    }

    return inorder_traversals;

} // static std::vector<std::vector<int>> swapNodesDiscussionSolution( ...

// Try sample input given in problem description
TEST(SwapNodesTest, SampleInput) {
    const std::vector<std::vector<int>> indexes {
        {2, 3},
        {-1, -1},
        {-1, -1}};

    const std::vector<int> queries {1, 1};

    EXPECT_EQ(queries.size(), swapNodesFirstAttempt(indexes, queries).size());

    const std::vector<std::vector<int>> expected_inorder_traversal {
        {3, 1, 2},
        {2, 1, 3}};

    const auto inorder_vec = swapNodesDiscussionSolution(indexes, queries);
    EXPECT_TRUE(std::equal(expected_inorder_traversal.front().cbegin(),
                           expected_inorder_traversal.front().cend(),
                           inorder_vec.front().cbegin()));
    
    EXPECT_TRUE(std::equal(expected_inorder_traversal.back().cbegin(),
                           expected_inorder_traversal.back().cend(),
                           inorder_vec.back().cbegin()));
}

// Test case 2
TEST(SwapNodesTest, TestCase2) {
    const std::vector<std::vector<int>> indexes {
        {2, 3},
        {4, 5},
        {6, -1},
        {-1, 7},
        {8, 9},
        {10, 11},
        {12, 13},
        {-1, 14},
        {-1, -1},
        {15, -1},
        {16, 17},
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1},
        {-1, -1}};

    const std::vector<int> queries {2, 3};

    const std::vector<std::vector<int>> expected_inorder_traversal {
        {14, 8, 5, 9, 2, 4, 13, 7, 12, 1, 3, 10, 15, 6, 17, 11, 16},
        {9, 5, 14, 8, 2, 13, 7, 12, 4, 1, 3, 17, 11, 16, 6, 10, 15}};
    
    const auto inorder_vec = swapNodesDiscussionSolution(indexes, queries);
    EXPECT_TRUE(std::equal(expected_inorder_traversal.front().cbegin(),
                           expected_inorder_traversal.front().cend(),
                           inorder_vec.front().cbegin()));
    
    EXPECT_TRUE(std::equal(expected_inorder_traversal.back().cbegin(),
                           expected_inorder_traversal.back().cend(),
                           inorder_vec.back().cbegin()));
}

// Test case 3
TEST(SwapNodesTest, TestCase3) {
    const std::vector<std::vector<int>> indexes {
        {2, 3},
        {4, -1},
        {5, -1},
        {6, -1},
        {7, 8},
        {-1, 9},
        {-1, -1},
        {10, 11},
        {-1, -1},
        {-1, -1},
        {-1, -1}};

    const std::vector<int> queries {2, 4};

    const std::vector<std::vector<int>> expected_inorder_traversal {
        {2, 9, 6, 4, 1, 3, 7, 5, 11, 8, 10},
        {2, 6, 9, 4, 1, 3, 7, 5, 10, 8, 11}};
    
    const auto inorder_vec = swapNodesDiscussionSolution(indexes, queries);
    EXPECT_TRUE(std::equal(expected_inorder_traversal.front().cbegin(),
                           expected_inorder_traversal.front().cend(),
                           inorder_vec.front().cbegin()));
    
    EXPECT_TRUE(std::equal(expected_inorder_traversal.back().cbegin(),
                           expected_inorder_traversal.back().cend(),
                           inorder_vec.back().cbegin()));
}