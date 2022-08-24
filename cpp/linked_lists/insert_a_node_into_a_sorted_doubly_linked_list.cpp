#include "doubly_linked_list_node.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist,
                                          int                   data)
{
    if (llist == nullptr)
    {
        return new DoublyLinkedListNode(data);
    }
    
    auto* node = new DoublyLinkedListNode(data);
    
    if (data < llist->data)
    {
        node->next  = llist;
        llist->prev = node;
        return node;
    }
    
    DoublyLinkedListNode* prev {nullptr};
    auto*                 curr = llist;
    while (curr != nullptr && data > curr->data)
    {
        prev = curr;
        curr = curr->next;
    }
    
    //! Set prev's next to node and node's prev to prev
    prev->next = node;
    node->prev = prev;
    
    if (curr != nullptr)
    {
        //! Set node's next to curr and curr's prev to node
        node->next = curr;
        curr->prev = node;   
    }
    
    return llist;

} // static DoublyLinkedListNode* sortedInsert( ...

//! @brief Solution from HR discussion section
//! @param[in] llist Pointer to head of doubly-linked list
//! @param[in] data  Value of data field for DoublyLinkedListNode to insert
//! @return Pointer to head of doubly-linked list
static DoublyLinkedListNode* sortedInsertDiscussionSolution(
    DoublyLinkedListNode* llist,
    int                   data)
{
    auto* node = new DoublyLinkedListNode(data);

    if (llist == nullptr)
    {
        return node;
    }
    else if (data < llist->data)
    {
        node->next  = llist;
        llist->prev = node;
        return node;
    }
    else
    {
        auto* rest  = sortedInsertDiscussionSolution(llist->next, data);
        llist->next = rest;
        rest->prev  = llist;
        return llist;
    }

} // static DoublyLinkedListNode* sortedInsertDiscussionSolution( ...

// Test case 0
TEST(SortedInsertTest, TestCase0) {
    DoublyLinkedList llist {};
    llist.insert_node(1);
    llist.insert_node(3);
    llist.insert_node(4);
    llist.insert_node(10);

    auto*      result_head = sortedInsert(llist.head, 5);
    const auto result_data = DoublyLinkedList::print(result_head);

    const std::vector<int> expected_data {1, 3, 4, 5, 10};
    
    EXPECT_TRUE(std::equal(expected_data.cbegin(),
                           expected_data.cend(),
                           result_data.cbegin()));
    
    DoublyLinkedList llistDS {};
    llistDS.insert_node(1);
    llistDS.insert_node(3);
    llistDS.insert_node(4);
    llistDS.insert_node(10);

    auto*      result_head_DS = sortedInsertDiscussionSolution(llistDS.head, 5);
    const auto result_data_DS = DoublyLinkedList::print(result_head_DS);

    EXPECT_TRUE(std::equal(expected_data.cbegin(),
                           expected_data.cend(),
                           result_data_DS.cbegin()));
}

// Test case 1
TEST(SortedInsertTest, TestCase1) {
    DoublyLinkedList llist {};
    llist.insert_node(2);
    llist.insert_node(3);
    llist.insert_node(4);

    auto*      result_head = sortedInsert(llist.head, 1);
    const auto result_data = DoublyLinkedList::print(result_head);

    const std::vector<int> expected_data {1, 2, 3, 4};
    
    EXPECT_TRUE(std::equal(expected_data.cbegin(),
                           expected_data.cend(),
                           result_data.cbegin()));
    
    DoublyLinkedList llistDS {};
    llistDS.insert_node(2);
    llistDS.insert_node(3);
    llistDS.insert_node(4);

    auto*      result_head_DS = sortedInsertDiscussionSolution(llistDS.head, 1);
    const auto result_data_DS = DoublyLinkedList::print(result_head_DS);

    EXPECT_TRUE(std::equal(expected_data.cbegin(),
                           expected_data.cend(),
                           result_data_DS.cbegin()));
}

// Test case 7
TEST(SortedInsertTest, TestCase7) {
    DoublyLinkedList llist {};
    llist.insert_node(1);
    llist.insert_node(2);
    llist.insert_node(3);

    auto*      result_head = sortedInsert(llist.head, 4);
    const auto result_data = DoublyLinkedList::print(result_head);

    const std::vector<int> expected_data {1, 2, 3, 4};
    
    EXPECT_TRUE(std::equal(expected_data.cbegin(),
                           expected_data.cend(),
                           result_data.cbegin()));

    DoublyLinkedList llistDS {};
    llistDS.insert_node(1);
    llistDS.insert_node(2);
    llistDS.insert_node(3);

    auto*      result_head_DS = sortedInsertDiscussionSolution(llistDS.head, 4);
    const auto result_data_DS = DoublyLinkedList::print(result_head_DS);

    EXPECT_TRUE(std::equal(expected_data.cbegin(),
                           expected_data.cend(),
                           result_data_DS.cbegin()));
}