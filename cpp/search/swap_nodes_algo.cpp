#include <gtest/gtest.h>

#include <algorithm>
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

// Try sample input given in problem description
TEST(SwapNodesTest, SampleInput) {
    std::vector<std::vector<int>> indexes {
        {2, 3},
        {-1, -1},
        {-1, -1}};

    std::vector<int> queries {1, 1};

    EXPECT_EQ(queries.size(), swapNodesFirstAttempt(indexes, queries).size());
}