#include "LC_tree_node.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <utility>
#include <vector>

static std::vector<std::vector<int>> levelOrderIterative(LC::TreeNode* root)
{
    // Store level order traversal
    std::vector<std::vector<int>> level_order {};

    // Store all nodes within a given level
    std::vector<LC::TreeNode*> level_nodes {};

    // Initialize level_nodes with root if not a nullptr
    if (nullptr != root)
    {
        level_nodes.push_back(root);
    }

    while (not level_nodes.empty())
    {
        // Size of initial level_nodes vector to distinguish
        // from child nodes that will be added
        auto init_size = level_nodes.size();

        // Loop over current node(s) in level
        std::vector<int> values_in_level(init_size);
        for (std::size_t i = 0; i < init_size; ++i)
        {
            const auto curr_node = level_nodes.at(i);

            // Add each value to values_in_level
            values_in_level.at(i) = curr_node->val_;

            // Copy their non-nullptr children to level_nodes
            if (nullptr != curr_node->left_)
            {
                level_nodes.push_back(curr_node->left_);
            }
            if (nullptr != curr_node->right_)
            {
                level_nodes.push_back(curr_node->right_);
            }
        }
        
        // Have added all value(s) from current node(s) in level
        // Move values_in_level into level_order
        level_order.emplace_back(std::move(values_in_level));

        if (init_size == level_nodes.size())
        {
            // No child nodes were added so just clear level_nodes
            level_nodes.clear();
        }
        else
        {
            // Erase first init_size nodes from level_nodes,
            // leaving any of their children in level_nodes
            level_nodes.erase(level_nodes.begin(),
                              level_nodes.begin() + init_size);
        }

    } // while (not level_nodes.empty())

    return level_order;

} // static std::vector<std::vector<int>> levelOrderIterative( ...

//! Helper function for recursive solution
//! @param[in]     root        Pointer to root TreeNode
//! @param[in]     depth       Current depth in tree
//! @param[in,out] level_order Reference to output vector of vectors
static void RecursiveHelper(LC::TreeNode*                  root,
                            std::size_t                    depth,
                            std::vector<std::vector<int>>& level_order)
{
    if (nullptr == root)
    {
        return;
    }

    if (depth == level_order.size())
    {
        // Prepare output vector for another level
        level_order.resize(depth + 1ULL);
    }
    
    level_order.at(depth).emplace_back(root->val_);
    RecursiveHelper(root->left_, depth + 1ULL, level_order);
    RecursiveHelper(root->right_, depth + 1ULL, level_order);

} // static void RecursiveHelper( ...

//! @brief Recursive solution from discussion section
//! @param[in] root Pointer to root TreeNode
//! @return Level order traversal as a vector of level values (vector)
static std::vector<std::vector<int>> levelOrderLCRecursive(LC::TreeNode* root)
{
    //! @details Referenced
    //!          https://leetcode.com/problems/binary-tree-level-order-traversal
    //!          /discuss/33468/One-of-C%2B%2B-solutions-(preorder)
    //!
    //!          Implements preorder traversal to achieve level order traversal.
    //!          Adds node's value to vector of current level values then looks
    //!          at its left and right children.
    //!
    //!          For a lean tree (most non-leaf nodes have only one child), this
    //!          DFS approach consumes O(n) memory. For a near complete tree
    //!          (most non-leaf nodes have two children), this DFS approach
    //!          costs O(log n) memory.

    std::vector<std::vector<int>> level_order {};
    RecursiveHelper(root, 0, level_order);
    return level_order;
}

// Try sample input given in problem description
TEST(LevelOrderTraversalTest, SampleInput) {
    // Create binary tree
    //   3
    //  / \
    // 9  20
    //   / \
    // 15   7
    LC::TreeNode seven {7};
    LC::TreeNode fifteen {15};
    LC::TreeNode twenty {20, &fifteen, &seven};
    LC::TreeNode nine {9};
    LC::TreeNode root {3, &nine, &twenty};

    // Expected level order traversal
    const std::vector<std::vector<int>> level_order {
        {3},
        {9, 20},
        {15, 7}};

    EXPECT_EQ(3ULL, level_order.size());

    const auto iterative = levelOrderIterative(&root);
    EXPECT_EQ(level_order.size(), iterative.size());

    EXPECT_TRUE(std::equal(level_order.front().cbegin(),
                           level_order.front().cend(),
                           iterative.front().cbegin()));

    EXPECT_TRUE(std::equal(level_order.at(1ULL).cbegin(),
                           level_order.at(1ULL).cend(),
                           iterative.at(1ULL).cbegin()));

    EXPECT_TRUE(std::equal(level_order.back().cbegin(),
                           level_order.back().cend(),
                           iterative.back().cbegin()));
    
    const auto recursive = levelOrderLCRecursive(&root);
    EXPECT_EQ(level_order.size(), recursive.size());

    EXPECT_TRUE(std::equal(level_order.front().cbegin(),
                           level_order.front().cend(),
                           recursive.front().cbegin()));

    EXPECT_TRUE(std::equal(level_order.at(1ULL).cbegin(),
                           level_order.at(1ULL).cend(),
                           recursive.at(1ULL).cbegin()));

    EXPECT_TRUE(std::equal(level_order.back().cbegin(),
                           level_order.back().cend(),
                           recursive.back().cbegin()));

} // TEST(LevelOrderTraversalTest, SampleInput) { ...