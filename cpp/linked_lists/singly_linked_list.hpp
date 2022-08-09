#include <cstdlib>

/*
 * Following code is copied from HR, with modifications
 */

class SinglyLinkedListNode
{
public:
    int                   data {};
    SinglyLinkedListNode* next {nullptr};

    SinglyLinkedListNode()  = default;
    ~SinglyLinkedListNode() = default;

    explicit SinglyLinkedListNode(int node_data)
        : data {node_data}
    {
    }
};

class SinglyLinkedList
{
public:
    SinglyLinkedListNode* head {nullptr};
    SinglyLinkedListNode* tail {nullptr};

    SinglyLinkedList()  = default;
    ~SinglyLinkedList() = default;

    void insert_node(int node_data)
    {
        SinglyLinkedListNode* node = new SinglyLinkedListNode(node_data);

        if (!this->head)
        {
            this->head = node;
        }
        else
        {
            this->tail->next = node;
        }

        this->tail = node;
    }
};

static void free_singly_linked_list(SinglyLinkedListNode* node)
{
    while (node)
    {
        SinglyLinkedListNode* temp = node;
        node = node->next;

        std::free(temp);
    }
}