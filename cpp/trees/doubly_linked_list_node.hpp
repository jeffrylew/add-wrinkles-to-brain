/*
 * Following code is copied from HR, with modifications
 */

#include <cstdlib>

class DoublyLinkedListNode
{
public:
    int data {};
    DoublyLinkedListNode* next {nullptr};
    DoublyLinkedListNode* prev {nullptr};

    DoublyLinkedListNode()  = default;
    ~DoublyLinkedListNode() = default;

    explicit DoublyLinkedListNode(int node_data)
        : data {node_data}
    {
    }
};

class DoublyLinkedList
{
public:
    DoublyLinkedListNode* head {nullptr};
    DoublyLinkedListNode* tail {nullptr};

    DoublyLinkedList() = default;

    ~DoublyLinkedList()
    {
        auto* node = head;

        while (node)
        {
            auto* temp = node;
            node       = node->next;
            std::free(temp);
        }

        head = nullptr;
        tail = nullptr;
    }

    void insert_node(int node_data)
    {
        auto* node = new DoublyLinkedListNode(node_data);

        if (!this->head)
        {
            this->head = node;
        }
        else
        {
            this->tail->next = node;
            node->prev       = this->tail;
        }

        this->tail = node;
    }
};