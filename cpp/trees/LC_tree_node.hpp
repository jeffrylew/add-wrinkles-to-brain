# ifndef CPP_TREES_LC_TREE_NODE_HPP_
# define CPP_TREES_LC_TREE_NODE_HPP_

//! @file LC_tree_node.hpp
//! @brief LC definition for a binary tree node (with modifications)

//! @namespace LC
//! @brief Indicates this code is from LC
namespace LC
{
//! @class TreeNode
//! @brief Definition for a binary tree node
class TreeNode
{
public:
    int       val_ {};
    TreeNode* left_ {nullptr};
    TreeNode* right_ {nullptr};

    TreeNode() = default;
    
    //! @brief TreeNode constructor initializing val_
    //! @param[in] val Initializer for val_ as int
    explicit TreeNode(int val)
        : val_ {val}
    {
    }

    //! @brief TreeNode constructor initializing all member variables
    //! @param[in] val   Initializer for val_ as int
    //! @param[in] left  Pointer to left TreeNode
    //! @param[in] right Pointer to right TreeNode
    TreeNode(int val, TreeNode* left, TreeNode* right)
        : val_ {val}
        , left_ {left}
        , right_ {right}
    {
    }

    //! Copy/move constructors and assignment operators (use shallow copies)
    TreeNode(const TreeNode&) = default;
    TreeNode(TreeNode&&)      = default;
    TreeNode& operator=(const TreeNode&) = default;
    TreeNode& operator=(TreeNode&&) = default;

}; // class TreeNode

} // namespace LC

#endif /* CPP_TREES_LC_TREE_NODE_HPP_ */