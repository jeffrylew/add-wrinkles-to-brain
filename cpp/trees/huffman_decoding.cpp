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
    spq              pq {};
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

} // namespace Huffman
