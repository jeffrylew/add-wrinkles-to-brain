#include "node.hpp"

#include <gtest/gtest.h>

#include <vector>

//! @brief Helper function to get inorder traversal of tree recursively
//! @param[in]  root      Pointer to root Node
//! @param[out] node_data Vector containing inorder traversal
static void inorder_traversal_recursive(Node* root, std::vector<int>& node_data)
{
    if (root == nullptr)
    {
        return;
    }

    inorder_traversal_recursive(root->left, node_data);
    node_data.emplace_back(root->data);
    inorder_traversal_recursive(root->right, node_data);
}

//! @brief Check if tree is a binary search tree recursively
//! @param[in] root Pointer to root Node
//! @return True if tree is a binary search tree, else false
static bool checkBSTRecursive(Node* root)
{
    std::vector<int> node_data {};

    inorder_traversal_recursive(root, node_data);

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

    // Clean up memory manually, HR code has memory leaks...
    delete root->right->right->right->right->right->right;
    delete root->right->right->right->right->right;
    delete root->right->right->right->right;
    delete root->right->right->right;
    delete root->right->right;
    delete root->right;
    delete root;
}