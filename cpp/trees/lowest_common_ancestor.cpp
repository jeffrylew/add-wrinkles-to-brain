#include "node.hpp"

#include <gtest/gtest.h>

//! @brief Recursive solution from discussion section
//! @param[in] root Pointer to root Node
//! @param[in] v1   Node value
//! @param[in] v2   Node value
//! @return Pointer to lowest common ancestor node of nodes storing v1 and v2
static Node* lcaDiscussionSolution(Node* root, int v1, int v2)
{
    //! @details Value of a common ancestor has to be between the two values
    //!          in a binary search tree
    //!
    //!          Time complexity: O(log n) on balanced tree (binary search tree)
    //!          Space complexity: O(log n) for stack calls

    //! root value is smaller than both
    if (root->data < v1 && root->data < v2)
    {
        return lcaDiscussionSolution(root->right, v1, v2);
    }
    
    //! root value is bigger than both
    if (root->data > v1 && root->data > v2)
    {
        return lcaDiscussionSolution(root->left, v1, v2);
    }
    
    //! Otherwise solution already found
    return root;

} // static Node* lcaDiscussionSolution( ...

//! @brief Iterative solution from discussion section
//! @param[in] root Pointer to root Node
//! @param[in] v1   Node value
//! @param[in] v2   Node value
//! @return Pointer to lowest common ancestor node of nodes storing v1 and v2
static Node* lcaIterative(Node* root, int v1, int v2)
{
    //! @details Value of a common ancestor has to be between the two values
    //!          in a binary search tree
    //!
    //!          Time complexity: O(log n) on balanced tree (binary search tree)
    //!          Space complexity: O(1)

    while (root != nullptr)
    {
        if (root->data > v1 && root->data > v2)
        {
            root = root->left;
        }
        else if (root->data < v1 && root->data < v2)
        {
            root = root->right;
        }
        else
        {
            break;
        }
    }
    
    return root;

} // static Node* lcaIterative( ...

// Test case 0
TEST(LCATest, TestCase0) {
    Node* root {nullptr};

    root = Tree::insert(root, 4);
    root = Tree::insert(root, 2);
    root = Tree::insert(root, 3);
    root = Tree::insert(root, 1);
    root = Tree::insert(root, 7);
    root = Tree::insert(root, 6);

    auto lowest_common_ancestor = lcaDiscussionSolution(root, 1, 7);
    EXPECT_EQ(4, lowest_common_ancestor->data);

    auto lowest_common_ancestor2 = lcaIterative(root, 1, 7);
    EXPECT_EQ(4, lowest_common_ancestor2->data);

    // Clean up memory manually, HR code has memory leaks...
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right->left;
    delete root->right;
    delete root;
}

// Test case 5
TEST(LCATest, TestCase5) {
    Node* root {nullptr};

    root = Tree::insert(root, 1);
    root = Tree::insert(root, 2);

    auto lowest_common_ancestor = lcaDiscussionSolution(root, 1, 2);
    EXPECT_EQ(1, lowest_common_ancestor->data);

    auto lowest_common_ancestor2 = lcaIterative(root, 1, 2);
    EXPECT_EQ(1, lowest_common_ancestor2->data);

    // Clean up memory manually, HR code has memory leaks...
    delete root->right;
    delete root;
}