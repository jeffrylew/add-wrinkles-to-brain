#include "LC_tree_node.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <stack>
#include <tuple>
#include <vector>

static std::vector<int> postorderTraversalIterative(LC::TreeNode* root)
{
    //! @details Referenced http://faculty.cs.niu.edu/~mcmahon/CS241/Notes/
    //!          Data_Structures/binary_tree_traversals.html
    //!
    //!          O(n) time and O(n) space

    // Vector to hold postorder traversal values
    std::vector<int> node_vals {};

    // Stack to backtrack up tree from node to its parent
    std::stack<LC::TreeNode*> todo {};

    // Pointer to node
    LC::TreeNode* curr_node = root;

    // Pointer to node last visited, distinguish between backtrack to node after
    // traversing left subtree versus backtracking to node after traversing its
    // right subtree
    LC::TreeNode* last_visited {nullptr};

    while (nullptr != curr_node && root != last_visited)
    {
        while (nullptr != curr_node && last_visited != curr_node)
        {
            // Copy curr_node to todo stack before
            // traversing the node's left subtree
            todo.push(curr_node);

            curr_node = curr_node->left_;
        }

        // curr_node is nullptr or last_visited here so backtrack one level
        curr_node = todo.top();
        todo.pop();

        // If node has no right child or
        // we've already traversed its right subtree
        if (nullptr == curr_node->right_ || last_visited == curr_node->right_)
        {
            // Add current node value to node_vals
            node_vals.emplace_back(curr_node->val_);

            // Mark this node as the last visited
            last_visited = curr_node;
        }
        else
        {
            // Traverse node's right subtree
            todo.push(curr_node);

            curr_node = curr_node->right_;

        } // if (nullptr == curr_node->right_ || ...

    } // while (nullptr != root && ...
    
    return node_vals;

} // static std::vector<int> postorderTraversalIterative( ...

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
    RecursiveHelper(root->right_, node_vals);
    node_vals.emplace_back(root->val_);

} // static void RecursiveHelper( ...

static std::vector<int> postorderTraversalRecursive(LC::TreeNode* root)
{
    //! @details O(n) time and O(n) space (function call stack)

    std::vector<int> node_vals {};
    RecursiveHelper(root, node_vals);
    return node_vals;
}

//! @brief LC discussion solution (iterative) using stack
//! @param[in] root Pointer to root TreeNode
//! @return Vector containing postorder traversal of integer node values
static std::vector<int> postorderTraversalLCIterative(LC::TreeNode* root)
{
    //! @details Referenced
    //!          https://leetcode.com/problems/binary-tree-postorder-traversal/
    //!          discuss/45550/C%2B%2B-Iterative-Recursive-and-Morris-Traversal
    //!
    //!          O(n) time and O(n) space

    std::vector<int>          node_vals {};
    std::stack<LC::TreeNode*> todo {};

    LC::TreeNode* last = nullptr;

    while (nullptr != root || not todo.empty())
    {
        if (nullptr != root)
        {
            todo.push(root);

            root = root->left_;
        }
        else
        {
            LC::TreeNode* node = todo.top();
            if (nullptr != node->right_ && last != node->right_)
            {
                root = node->right_;
            }
            else
            {
                node_vals.push_back(node->val_);

                last = node;
                todo.pop();
            }

        } // else -> if (nullptr != root)

    } // while (nullptr != root || ...
    
    return node_vals;

} // static std::vector<int> postorderTraversalLCIterative( ...

//! @brief LC discussion solution using Morris traversal
//! @param[in] root Pointer to root TreeNode
//! @return Vector containing postorder traversal of integer node values
static std::vector<int> postorderTraversalLCMorris(LC::TreeNode* root)
{
    //! @details Referenced
    //!          https://leetcode.com/problems/binary-tree-postorder-traversal/
    //!          discuss/45550/C%2B%2B-Iterative-Recursive-and-Morris-Traversal
    //!
    //!          "Reversed" preorder Morris traversal
    //!
    //!          O(n) time and O(1) space

    std::vector<int> node_vals {};

    while (nullptr != root)
    {
        if (nullptr != root->right_)
        {
            auto* pre = root->right_;
            while (nullptr != pre->left_ && root != pre->left_)
            {
                pre = pre->left_;
            }
            
            // Exited while loop so check conditions that caused exit
            if (nullptr == pre->left_)
            {
                // Note: Adding to beginning of vector is inefficient,
                //       could use a queue instead and transfer to vector
                pre->left_ = root;
                node_vals.emplace(node_vals.begin(), root->val_);
                root = root->right_;
            }
            else
            {
                // pre->left_ is not nullptr but is equal to root
                pre->left_ = nullptr;
                root       = root->left_;

            } // else -> if (nullptr == pre->left_)
        }
        else
        {
            // root->right_ is nullptr here
            // Note: Adding to beginning of vector is inefficient,
            //       could use a queue instead and transfer to vector
            node_vals.emplace(node_vals.begin(), root->val_);
            root = root->left_;

        } // else -> if (nullptr != root->right_)
        
    } // while (nullptr != root)
    
    return node_vals;

} // static std::vector<int> postorderTraversalLCMorris( ...

// Try sample input given in problem description
TEST(PostorderTraversalTest, SampleInput) {
    // Create binary tree
    // 1
    //  \
    //   2
    //  /
    // 3
    LC::TreeNode third {3};
    LC::TreeNode second {2, &third, nullptr};
    LC::TreeNode root {1, nullptr, &second};

    // Expected postorder traversal
    const std::vector<int> expected_vec {3, 2, 1};

    auto iterative_vec = postorderTraversalIterative(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           iterative_vec.cbegin()));

    const auto recursive_vec = postorderTraversalRecursive(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           recursive_vec.cbegin()));
    
    iterative_vec = postorderTraversalLCIterative(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           iterative_vec.cbegin()));

    const auto morris_vec = postorderTraversalLCMorris(&root);
    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           morris_vec.cbegin()));
}

// Test nullptr root input
TEST(PostorderTraversalTest, NullRoot) {
    EXPECT_TRUE(postorderTraversalIterative(nullptr).empty());
    EXPECT_TRUE(postorderTraversalRecursive(nullptr).empty());
    EXPECT_TRUE(postorderTraversalLCIterative(nullptr).empty());
    EXPECT_TRUE(postorderTraversalLCMorris(nullptr).empty());
}