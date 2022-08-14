#include "node.hpp"

#include <gtest/gtest.h>

#include <stack>
#include <vector>

//! @brief Helper function to get inorder traversal of tree recursively
//! @param[in]  root      Pointer to root Node
//! @param[out] node_data Vector containing inorder traversal
static void inorder_traversal_recursive(Node* root, std::vector<int>& node_data)
{
    //! @details Time complexity: O(n)
    //!          Space complexity: O(n)

    if (root == nullptr)
    {
        return;
    }

    inorder_traversal_recursive(root->left, node_data);
    node_data.emplace_back(root->data);
    inorder_traversal_recursive(root->right, node_data);
}

//! @brief Helper function to get inorder traversal of tree iteratively
//! @param[in]  root      Pointer to root Node
//! @param[out] node_data Vector containing inorder traversal
static void inorder_traversal_iterative(Node* root, std::vector<int>& node_data)
{
    //! @details Time complexity: O(n)
    //!          Space complexity: O(n)
    
    //! Stack to backtrack up tree from node to its parent
    std::stack<Node*> todo {};

    while (root != nullptr || not todo.empty())
    {
        if (root != nullptr)
        {
            //! Copy root to todo stack before
            //! traversing the node's left subtree
            todo.push(root);

            root = root->left;
        }
        else
        {
            //! root is nullptr here so backtrack one level
            root = todo.top();
            todo.pop();

            //! Add current node value to node_data
            node_data.emplace_back(root->data);

            //! We have visited the node and its left subtree,
            //! so now traverse node's right subtree
            root = root->right;

        } // else -> if (root != nullptr)

    } // while (root != nullptr || ...

} // static void inorder_traversal_iterative( ...

//! @brief Check if tree is a binary search tree recursively
//! @param[in] root Pointer to root Node
//! @return True if tree is a binary search tree, else false
static bool checkBSTRecursive(Node* root)
{
    std::vector<int> node_data {};

    inorder_traversal_recursive(root, node_data);

    //! Could also check if both of root's children are nullptr
    //! before the call to inorder_traversal_recursive
    if (1ULL == node_data.size())
    {
        return true;
    }
    
    for (std::size_t i = 1ULL; i < node_data.size(); ++i)
    {
        if (node_data[i] <= node_data[i - 1ULL])
        {
            return false;
        }
    }
    
    return true;

} // static bool checkBSTRecursive( ...

//! @brief Check if tree is a binary search tree iteratively
//! @param[in] root Pointer to root Node
//! @return True if tree is a binary search tree, else false
static bool checkBSTIterative(Node* root)
{
    std::vector<int> node_data {};

    inorder_traversal_iterative(root, node_data);

    //! Could also check if both of root's children are nullptr
    //! before the call to inorder_traversal_iterative
    if (1ULL == node_data.size())
    {
        return true;
    }
    
    for (std::size_t i = 1ULL; i < node_data.size(); ++i)
    {
        //! This check could also be performed in inorder_traversal_iterative
        if (node_data[i] <= node_data[i - 1ULL])
        {
            return false;
        }
    }
    
    return true;

} // static bool checkBSTIterative( ...

// Test case 0
TEST(CheckBSTTest, TestCase0) {
    Node* root {nullptr};

    root = Tree::insert(root, 1);
    root = Tree::insert(root, 2);
    root = Tree::insert(root, 3);
    root = Tree::insert(root, 4);
    root = Tree::insert(root, 5);
    root = Tree::insert(root, 6);
    root = Tree::insert(root, 7);

    EXPECT_TRUE(checkBSTRecursive(root));
    EXPECT_TRUE(checkBSTIterative(root));

    // Clean up memory manually, HR code has memory leaks...
    delete root->right->right->right->right->right->right;
    delete root->right->right->right->right->right;
    delete root->right->right->right->right;
    delete root->right->right->right;
    delete root->right->right;
    delete root->right;
    delete root;
}

// Test case 1
TEST(CheckBSTTest, TestCase1) {
    Node* root {nullptr};

    root = Tree::insert(root, 1);
    root = Tree::insert(root, 2);
    root = Tree::insert(root, 4);
    root->right->right->left                      = new Node(3);
    root->right->right->left->right               = new Node(5);
    root->right->right->left->right->right        = new Node(6);
    root->right->right->left->right->right->right = new Node(7);

    EXPECT_FALSE(checkBSTRecursive(root));
    EXPECT_FALSE(checkBSTIterative(root));

    // Clean up memory manually, HR code has memory leaks...
    delete root->right->right->left->right->right->right;
    delete root->right->right->left->right->right;
    delete root->right->right->left->right;
    delete root->right->right->left;
    delete root->right->right;
    delete root->right;
    delete root;
}

// Test case 14
TEST(CheckBSTTest, TestCase14) {
    Node* root {nullptr};

    root = Tree::insert(root, 3);
    root = Tree::insert(root, 5);
    root = Tree::insert(root, 7);
    root = Tree::insert(root, 9);
    root = Tree::insert(root, 11);
    root = Tree::insert(root, 13);
    root = Tree::insert(root, 15);

    EXPECT_TRUE(checkBSTRecursive(root));
    EXPECT_TRUE(checkBSTIterative(root));

    // Clean up memory manually, HR code has memory leaks...
    delete root->right->right->right->right->right->right;
    delete root->right->right->right->right->right;
    delete root->right->right->right->right;
    delete root->right->right->right;
    delete root->right->right;
    delete root->right;
    delete root;
}