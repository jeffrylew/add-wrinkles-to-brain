#include "LC_tree_node.hpp"

#include <gtest/gtest.h>

#include <algorithm>

static int heightRecursive(LC::TreeNode* root)
{
    //! @details O(n) time and O(2^n) space (function call stack)

    // Reached null node, height is 0
    if (nullptr == root)
    {
        return 0;
    }
    
    // Reached a leaf, a potential "bottom" of the tree
    // Since we are counting the number of edges, return 0
    // instead of 1 since the leaf doesn't contribute to the height
    if (nullptr == root->left_ && nullptr == root->right_)
    {
        return 0;
    }
    
    return 1 + std::max(heightRecursive(root->left_),
                        heightRecursive(root->right_));

} // static int heightRecursive( ...

// Try sample inputs given in problem description
TEST(HeightTest, SampleInput) {
    // Create binary tree1
    //       4
    //     /  \
    //   2     6
    //  / \   / \
    // 1   3 5   7
    LC::TreeNode tree1_one {1};
    LC::TreeNode tree1_three {3};
    LC::TreeNode tree1_five {5};
    LC::TreeNode tree1_seven {7};
    LC::TreeNode tree1_two {2, &tree1_one, &tree1_three};
    LC::TreeNode tree1_six {6, &tree1_five, &tree1_seven};
    LC::TreeNode tree1_root {4, &tree1_two, &tree1_six};

    EXPECT_EQ(2, heightRecursive(&tree1_root));

    // Create binary tree2
    //       3
    //     /  \
    //   2     5
    //  /     / \
    // 1     4   6
    //            \
    //             7
    LC::TreeNode tree2_seven {7};
    LC::TreeNode tree2_six {6, nullptr, &tree2_seven};
    LC::TreeNode tree2_four {4};
    LC::TreeNode tree2_one {1};
    LC::TreeNode tree2_two {2, &tree2_one, nullptr};
    LC::TreeNode tree2_five {5, &tree2_four, &tree2_six};
    LC::TreeNode tree2_root {3, &tree2_two, &tree2_five};

    EXPECT_EQ(3, heightRecursive(&tree2_root));
}

// Test case 4
TEST(HeightTest, TestCase4) {
    LC::TreeNode root {15};

    EXPECT_EQ(0, heightRecursive(&root));
}