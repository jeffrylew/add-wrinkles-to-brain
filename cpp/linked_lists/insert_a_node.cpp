#include "singly_linked_list.hpp"

#include <gtest/gtest.h>

static SinglyLinkedListNode* insertNodeAtPosition(
    SinglyLinkedListNode* llist,
    int                   data,
    int                   position)
{
    // New pointer to node with input data (new = disgusting...)
    auto* node = new SinglyLinkedListNode {data};
    node->next = nullptr;
    
    // If llist head is nullptr, node is the new head
    if (llist == nullptr)
    {
        llist = node;
        return llist;
    }
    
    // Insertion at beginning of list, node is the new head
    if (position == 0)
    {
        // Save previous head position
        auto prev_head = llist;
        
        // Set node's next to prev_head
        node->next = prev_head;
        
        // Set llist to node, the new head
        llist = node;
        return llist;
    }
    
    // Pointer to previous node
    SinglyLinkedListNode* prev {nullptr};
    
    // Pointer to next node, initialized to head
    auto next = llist;
    
    // Find position
    while (position > 0)
    {
        prev = next;
        next = next->next;
        --position;
    }
    
    // Set node's next to next
    node->next = next;
    
    // Set prev's next to node
    prev->next = node;
    
    return llist;

} // static SinglyLinkedListNode* insertNodeAtPosition( ...

//! @brief Solution from discussion section
//! @param[in] llist    Pointer to list head
//! @param[in] data     Data for new node as an int
//! @param[in] position Position to insert new node, zero based indexing
//! @return Pointer to head of revised list
static SinglyLinkedListNode* insertNodeAtPositionDiscussionSolution(
    SinglyLinkedListNode* llist,
    int                   data,
    int                   position)
{
    auto* new_node = new SinglyLinkedListNode {data};
    auto  current  = llist;

    if (position == 0)
    {
        new_node->next = llist;
        return new_node;
    }
    
    int idx {};
    while (++idx < position)
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next  = new_node;

    return llist;

} // static SinglyLinkedListNode* insertNodeAtPositionDiscussionSolution( ...

// Try sample input given in problem description
TEST(InsertNodeTest, SampleInput) {
    // Initialize SinglyLinkedList
    SinglyLinkedList* llist = new SinglyLinkedList();
    llist->insert_node(1);
    llist->insert_node(2);
    llist->insert_node(3);

    // Define test values for node to insert
    constexpr int data {4};
    constexpr int pos {2};

    auto llist_head = insertNodeAtPosition(llist->head, data, pos);

    // Create pointer for iterating
    auto iter = llist_head;

    // Iterate to newly inserted node
    for (int i = 0; i < pos; ++i)
    {
        iter = iter->next;
    }
    
    EXPECT_EQ(data, iter->data);
    EXPECT_EQ(3, iter->next->data);

    // Free allocated memory
    free_singly_linked_list(llist_head);

    // Now test discussion solution

    // Initialize SinglyLinkedList
    SinglyLinkedList* llist2 = new SinglyLinkedList();
    llist2->insert_node(1);
    llist2->insert_node(2);
    llist2->insert_node(3);

    auto llist_head2 = insertNodeAtPositionDiscussionSolution(
        llist2->head, //
        data,         //
        pos);

    // Create pointer for iterating
    auto iter2 = llist_head2;

    // Iterate to newly inserted node
    for (int i = 0; i < pos; ++i)
    {
        iter2 = iter2->next;
    }
    
    EXPECT_EQ(data, iter2->data);
    EXPECT_EQ(3, iter2->next->data);

    // Free allocated memory
    free_singly_linked_list(llist_head2);
}

// Test case 0
TEST(InsertNodeTest, TestCase0) {
    // Initialize SinglyLinkedList
    SinglyLinkedList* llist = new SinglyLinkedList();
    llist->insert_node(16);
    llist->insert_node(13);
    llist->insert_node(7);

    // Define test values for node to insert
    constexpr int data {1};
    constexpr int pos {2};

    auto llist_head = insertNodeAtPosition(llist->head, data, pos);

    // Create pointer for iterating
    auto iter = llist_head;

    // Iterate to newly inserted node
    for (int i = 0; i < pos; ++i)
    {
        iter = iter->next;
    }
    
    EXPECT_EQ(data, iter->data);
    EXPECT_EQ(7, iter->next->data);

    // Free allocated memory
    free_singly_linked_list(llist_head);
}

// Test case 1
TEST(InsertNodeTest, TestCase1) {
    // Initialize SinglyLinkedList
    SinglyLinkedList* llist = new SinglyLinkedList();
    llist->insert_node(11);
    llist->insert_node(9);
    llist->insert_node(19);
    llist->insert_node(10);
    llist->insert_node(4);

    // Define test values for node to insert
    constexpr int data {20};
    constexpr int pos {3};

    auto llist_head = insertNodeAtPosition(llist->head, data, pos);

    // Create pointer for iterating
    auto iter = llist_head;

    // Iterate to newly inserted node
    for (int i = 0; i < pos; ++i)
    {
        iter = iter->next;
    }
    
    EXPECT_EQ(data, iter->data);
    EXPECT_EQ(10, iter->next->data);

    // Free allocated memory
    free_singly_linked_list(llist_head);
}

// Test case 9
TEST(InsertNodeTest, TestCase9) {
    // Initialize SinglyLinkedList
    SinglyLinkedList* llist = new SinglyLinkedList();
    llist->insert_node(1);
    llist->insert_node(2);
    llist->insert_node(3);
    llist->insert_node(4);
    llist->insert_node(5);
    llist->insert_node(6);

    // Define test values for node to insert
    constexpr int data {7};
    constexpr int pos {5};

    auto llist_head = insertNodeAtPosition(llist->head, data, pos);

    // Create pointer for iterating
    auto iter = llist_head;

    // Iterate to newly inserted node
    for (int i = 0; i < pos; ++i)
    {
        iter = iter->next;
    }
    
    EXPECT_EQ(data, iter->data);
    EXPECT_EQ(6, iter->next->data);

    // Free allocated memory
    free_singly_linked_list(llist_head);
}