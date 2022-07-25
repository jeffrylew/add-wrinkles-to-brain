#include "LC_tree_node.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <vector>

static std::vector<int> inorderTraversalIterative(LC::TreeNode* root)
{
    //! @details O(n) time and O(n) space

    // Vector to hold inorder traversal values
    std::vector<int> node_vals {};

    // Stack to backtrack up tree from node to its parent
    std::stack<LC::TreeNode*> todo {};

    while (nullptr != root || not todo.empty())
    {
        if (nullptr != root)
        {
            // Copy root to todo stack before
            // traversing the node's left subtree
            todo.push(root);

            root = root->left_;
        }
        else
        {
            // root is nullptr here so backtrack one level
            root = todo.top();
            todo.pop();

            // Add current node value to node_vals
            node_vals.emplace_back(root->val_);

            // We have visited the node and its left subtree,
            // so now traverse node's right subtree
            root = root->right_;

        } // else -> if (nullptr != root)

    } // while (nullptr != root || ...
    
    return node_vals;

} // static std::vector<int> inorderTraversalIterative( ...

//! @brief Helper function for recursive solution
//! @param[in]  root      Pointer to root TreeNode
//! @param[out] node_vals Reference to output vector of node values
static void RecursiveHelper(LC::TreeNode* root, std::vector<int>& node_vals)
{
    if (nullptr == root)
    {
        return;
    }
    
    RecursiveHelper(root->left_, node_vals);
    node_vals.emplace_back(root->val_);
    RecursiveHelper(root->right_, node_vals);

} // static void RecursiveHelper( ...

static std::vector<int> inorderTraversalRecursive(LC::TreeNode* root)
{
    //! @details O(n) time O(n) space (function call stack)

    std::vector<int> node_vals {};
    RecursiveHelper(root, node_vals);
    return node_vals;
}

//! @brief Inorder traversal using Morris traversal
//! @param[in] root Pointer to root TreeNode
//! @return Vector containing inorder traversal of integer node values
static std::vector<int> inorderTraversalMorris(LC::TreeNode* root)
{
    //! @details O(n) time and O(1) space
    //!          Referenced:
    //!          https://leetcode.com/problems/binary-tree-inorder-traversal/
    //!          discuss/148939/CPP-Morris-Traversal

    // Vector to hold inorder traversal values
    std::vector<int> node_vals {};

    while (nullptr != root)
    {
        if (nullptr != root->left_)
        {
            // Create node that will serve as predecessor to root
            auto* predecessor = root->left_;
            while (nullptr != predecessor->right_
                   && root != predecessor->right_)
            {
                predecessor = predecessor->right_;
            }
            
            // Exited while loop so check condition that caused exit
            if (nullptr == predecessor->right_)
            {
                // Reached right child of rightmost node in root's left subtree
                // Set predecessor's right child to root
                predecessor->right_ = root;
                root = root->left_;
            }
            else
            {
                // predecessor->right_ is not nullptr but is equal to root
                // We are revisiting precedessor so revert the link to root
                predecessor->right_ = nullptr;
                node_vals.emplace_back(root->val_);
                root = root->right_;

            } // else -> if (nullptr == predecessor->right_)
        }
        else
        {
            // root->left_ is nullptr here
            node_vals.emplace_back(root->val_);
            root = root->right_;

        } // else -> if (nullptr != root->left_)

    } // while (nullptr != root)

    return node_vals;

} // static std::vector<int> inorderTraversalMorris( ...

// Try sample input given in problem description
TEST(InorderTraversalTest, SampleInput) {
    // Create binary tree
    // 1
    //  \
    //   2
    //  /
    // 3
    LC::TreeNode third {3};
    LC::TreeNode second {2, &third, nullptr};
    LC::TreeNode root {1, nullptr, &second};

    // Expected inorder traversal
    const std::vector<int> expected_vec {1, 3, 2};

    const auto iterative_vec = inorderTraversalIterative(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           iterative_vec.cbegin()));

    const auto recursive_vec = inorderTraversalRecursive(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           recursive_vec.cbegin()));

    const auto morris_vec = inorderTraversalMorris(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           morris_vec.cbegin()));
}

// Test nullptr root input
TEST(InorderTraversalTest, NullRoot) {
    EXPECT_TRUE(inorderTraversalIterative(nullptr).empty());
    EXPECT_TRUE(inorderTraversalRecursive(nullptr).empty());
    EXPECT_TRUE(inorderTraversalMorris(nullptr).empty());
}