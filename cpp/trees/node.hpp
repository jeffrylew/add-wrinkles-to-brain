/*
 * Following code is copied from HR, with modifications
 */

class Node
{
public:
    int   data {};
    Node* left {nullptr};
    Node* right {nullptr};

    Node()  = default;
    ~Node() = default;

    explicit Node(int d)
      : data {d}
    {
    }
};

namespace Tree
{
    Node* insert(Node* root, int data)
    {
        if (root == nullptr)
        {
            return new Node(data);
        }
        else
        {
            Node* cur {nullptr};

            if (data <= root->data)
            {
                cur = insert(root->left, data);
                root->left = cur;
            }
            else
            {
                cur = insert(root->right, data);
                root->right = cur;
            }

            return root;
        }
    }

} // namespace Tree
