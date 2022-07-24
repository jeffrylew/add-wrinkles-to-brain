#include "LC_tree_node.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <tuple>
#include <vector>

static std::vector<int> preorderTraversalIterative(LC::TreeNode* root)
{
    //! @details Referenced http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/
    //!          Data_Structures/binary_tree_traversals.html

    // Vector to hold preorder traversal values
    std::vector<int> traversal {};

    // Stack to backtrack up tree from node to its parent
    std::stack<LC::TreeNode*> node_stack {};

    auto node_ptr = root;
    while (nullptr != node_ptr || not node_stack.empty())
    {
        // Go all the way to the left
        while (nullptr != node_ptr)
        {
            // Visit node pointed to by node_ptr
            traversal.emplace_back(node_ptr->val_);

            // Copy node_ptr to node_stack before
            // traversing the node's left subtree
            node_stack.push(node_ptr);

            node_ptr = node_ptr->left_;
        }

        // node_ptr is nullptr here so backtrack one level
        node_ptr = node_stack.top();
        node_stack.pop();

        // We have visited the node and its left subtree,
        // so now traverse node's right subtree
        node_ptr = node_ptr->right_;

    } // while (nullptr != node_ptr || ...

    return traversal;

} // static std::vector<int> preorderTraversalIterative( ...

static std::vector<int> preorderTraversalRecursive(LC::TreeNode* root)
{
    //! @details Referenced http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/
    //!          Data_Structures/binary_tree_traversals.html

    // Vector to hold preorder traversal across function calls
    static std::vector<int> traversal {};

    // Need to "visit" a node then traverse both its subtrees
    if (nullptr != root)
    {
        // First, visit the node pointed to by input
        traversal.emplace_back(root->val_);

        // Traverse left subtree first
        std::ignore = preorderTraversalRecursive(root->left_);

        // Traverse right subtree last
        std::ignore = preorderTraversalRecursive(root->right_);
    }
    
    return traversal;

} // static std::vector<int> preorderTraversalRecursive( ...

//! @brief LC discussion solution (iterative) using stack
//! @param[in] root Pointer to root TreeNode
//! @return Vector containing preorder traversal of integer node values
static std::vector<int> preorderTraversalLCIterative(LC::TreeNode* root)
{
    //! @details O(n) time and O(n) space

    std::vector<int>          node_vals {};
    std::stack<LC::TreeNode*> todo {};

    while (nullptr != root || not todo.empty())
    {
        if (nullptr != root)
        {
            // Add current node value
            node_vals.emplace_back(root->val_);
            
            // Add copy of non-nullptr right child to todo stack
            if (nullptr != root->right_)
            {
                todo.push(root->right_);
            }
            
            root = root->left_;
        }
        else
        {
            // root is nullptr here so backtrack one level to right child
            root = todo.top();
            todo.pop();
        }

    } // while (nullptr != root || ...

    return node_vals;

} // static std::vector<int> preorderTraversalLCIterative( ...

//! @brief Helper function for LC recursive discussion solution
//! @param[in]  root      Pointer to root TreeNode
//! @param[out] node_vals Reference to output vector of node values
static void LCRecursiveHelper(LC::TreeNode* root, std::vector<int>& node_vals)
{
    if (nullptr == root)
    {
        return;
    }
    
    node_vals.emplace_back(root->val_);
    LCRecursiveHelper(root->left_, node_vals);
    LCRecursiveHelper(root->right_, node_vals);

} // static void LCRecursiveHelper( ...

//! @brief LC discussion solution (recursive)
//! @param[in] root Pointer to root TreeNode
//! @return Vector containing preorder traversal of integer node values
static std::vector<int> preorderTraversalLCRecursive(LC::TreeNode* root)
{
    //! @details O(n) time and O(n) space (function call stack)

    std::vector<int> node_vals {};
    LCRecursiveHelper(root, node_vals);
    return node_vals;
}

//! @brief LC discussion solution using Morris traversal
//! @param[in] root Pointer to root TreeNode
//! @return Vector containing preorder traversal of integer node values
static std::vector<int> preorderTraversalLCMorris(LC::TreeNode* root)
{
    //! @details O(n) time and O(1) space

    std::vector<int> node_vals {};

    while (nullptr != root)
    {
        if (nullptr != root->left_)
        {
            auto* pre = root->left_;
            while (nullptr != pre->right_ && root != pre->right_)
            {
                pre = pre->right_;
            }
            
            // Exited while loop so check conditions that caused exit
            if (nullptr == pre->right_)
            {
                pre->right_ = root;
                node_vals.emplace_back(root->val_);
                root = root->left_;
            }
            else
            {
                // pre->right_ is not nullptr but is equal to root
                pre->right_ = nullptr;
                root        = root->right_;

            } // else -> if (nullptr == pre->right_)
        }
        else
        {
            // root->left_ is nullptr here
            node_vals.emplace_back(root->val_);
            root = root->right_;

        } // else -> if (nullptr != root->left_)

    } // while (nullptr != root)

    return node_vals;

} // static std::vector<int> preorderTraversalLCMorris( ...

// Try sample input given in problem description
TEST(PreorderTraversalTest, SampleInput) {
    // Create binary tree
    // 1
    //  \
    //   2
    //  /
    // 3
    LC::TreeNode third {3};
    LC::TreeNode second {2, &third, nullptr};
    LC::TreeNode root {1, nullptr, &second};

    // Expected preorder traversal
    const std::vector<int> expected_vec {1, 2, 3};

    auto iterative_vec = preorderTraversalIterative(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           iterative_vec.cbegin()));

    auto recursive_vec = preorderTraversalRecursive(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           recursive_vec.cbegin()));

    iterative_vec = preorderTraversalLCIterative(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           iterative_vec.cbegin()));

    recursive_vec = preorderTraversalLCRecursive(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           recursive_vec.cbegin()));

    const auto morris_vec = preorderTraversalLCMorris(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           morris_vec.cbegin()));
}

// Test nullptr root input
TEST(PreorderTraversalTest, NullRoot) {
    EXPECT_TRUE(preorderTraversalIterative(nullptr).empty());
    EXPECT_TRUE(preorderTraversalRecursive(nullptr).empty());
    EXPECT_TRUE(preorderTraversalLCIterative(nullptr).empty());
    EXPECT_TRUE(preorderTraversalLCRecursive(nullptr).empty());
    EXPECT_TRUE(preorderTraversalLCMorris(nullptr).empty());
}