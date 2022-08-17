#include <gtest/gtest.h>

#include <map>
#include <queue>
#include <string>
#include <vector>

//! @namespace Huffman
//! @brief Contains framework (copied from HR with edits) for Huffman Decoding
namespace Huffman
{
//! @struct Node
//! @brief Defines a node in the Huffman tree
struct Node
{
    int   freq {};
    char  data {};
    Node* left {nullptr};
    Node* right {nullptr};
};

//! Use lambda to compare Node frequencies
auto deref_comp = [](const Node* lhs, const Node* rhs) -> bool {
    return lhs->freq > rhs->freq;
};

//! Define type alias for priority_queue
using spq =
    std::priority_queue<Node*, std::vector<Node*>, decltype(deref_comp)>;

Node* huffman_hidden(std::string s)
{
    spq              pq {deref_comp};
    std::vector<int> count(256ULL);

    for (int i = 0; i < s.size(); ++i)
    {
        ++count[s[i]];
    }
    
    for (int i = 0; i < 256; ++i)
    {
        Node* n_node  = new Node();
        n_node->left  = nullptr;
        n_node->right = nullptr;
        n_node->data  = static_cast<char>(i);
        n_node->freq  = count[i];

        if (count[i] != 0)
        {
            pq.push(n_node);
        }
    }
    
    while (1ULL != pq.size())
    {
        auto left = pq.top();
        pq.pop();
        auto right = pq.top();
        pq.pop();

        Node* comb  = new Node();
        comb->freq  = left->freq + right->freq;
        comb->data  = '\0';
        comb->left  = left;
        comb->right = right;
        pq.push(comb);
    }

    return pq.top();

} // Node* huffman_hidden(std::string s)

void print_codes_hidden(Node*                        root,
                        std::string                  code,
                        std::map<char, std::string>& mp)
{
    if (nullptr == root)
    {
        return;
    }

    if ('\0' != root->data)
    {
        mp[root->data] = code;
    }

    print_codes_hidden(root->left, code + '0', mp);
    print_codes_hidden(root->right, code + '1', mp);

} // void print_codes_hidden( ...

//! @brief Free allocated memory in Huffman tree
//! @param[in] root Pointer to root node of Huffman tree
void free_tree_memory(Huffman::Node* root)
{
    if (nullptr == root)
    {
        return;
    }
    
    //! Reached a leaf node, free the node's memory
    if (nullptr == root->left && nullptr == root->right)
    {
        delete root;
        root = nullptr;
        return;
    }

    if (nullptr != root->left)
    {
        free_tree_memory(root->left);
    }

    if (nullptr != root->right)
    {
        free_tree_memory(root->right);
    }

    //! Free current node memory after freeing memory of child nodes
    delete root;
    root = nullptr;

} // void free_tree_memory( ...

} // namespace Huffman

//! @brief Decode encoded string given Huffman tree
//! @param[in] root Pointer to root node of Huffman tree
//! @param[in] s    Huffman encoded string
//! @return Decoded string
static std::string decode_huff(Huffman::Node* root, std::string s)
{
    //! Node for iterating
    Huffman::Node* iter {root};

    //! String to hold decoded string
    std::string decoded_s {};
    
    for (const auto c : s)
    {
        //! Convert char to int
        int i = c - '0';
        
        if (0 == i)
        {
            //! Move to left child
            iter = iter->left;
        }
        else
        {
            //! Move to right child
            iter = iter->right;
        }
        
        if (nullptr == iter->left && nullptr == iter->right)
        {
            //! Reached a leaf node, add its value to decoded string
            // std::cout << iter->data;
            decoded_s += iter->data;
            
            //! Reset iterator node to root
            iter = root;
        }
        
    } // for (const auto c : s)
    
    return decoded_s;

} // static std::string decode_huff( ...

// Test case 2
TEST(DecodeHuffTest, TestCase2) {
    std::string decoded_str {"ABACA"};

    auto tree = Huffman::huffman_hidden(decoded_str);

    std::string                 code {};
    std::map<char, std::string> mp {};

    Huffman::print_codes_hidden(tree, code, mp);

    std::string coded {};

    for (const auto c : decoded_str)
    {
        coded += mp[c];
    }

    EXPECT_EQ(decoded_str, decode_huff(tree, coded));

    // Free allocated memory
    Huffman::free_tree_memory(tree);
}

// Test case 5
TEST(DecodeHuffTest, TestCase5) {
    std::string decoded_str {"Rumpelstiltskin"};

    auto tree = Huffman::huffman_hidden(decoded_str);

    std::string                 code {};
    std::map<char, std::string> mp {};

    Huffman::print_codes_hidden(tree, code, mp);

    std::string coded {};

    for (const auto c : decoded_str)
    {
        coded += mp[c];
    }

    EXPECT_EQ(decoded_str, decode_huff(tree, coded));

    // Free allocated memory
    Huffman::free_tree_memory(tree);
}

// Test case 6
TEST(DecodeHuffTest, TestCase6) {
    std::string decoded_str {
        "howmuchwoodwouldawoodchuckchuckifawoodchuckcouldchuckwood?"};

    auto tree = Huffman::huffman_hidden(decoded_str);

    std::string                 code {};
    std::map<char, std::string> mp {};

    Huffman::print_codes_hidden(tree, code, mp);

    std::string coded {};

    for (const auto c : decoded_str)
    {
        coded += mp[c];
    }

    EXPECT_EQ(decoded_str, decode_huff(tree, coded));

    // Free allocated memory
    Huffman::free_tree_memory(tree);
}