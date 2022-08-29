#include "doubly_linked_list_node.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static DoublyLinkedListNode* reverse(DoublyLinkedListNode* llist)
{
    if (llist == nullptr || llist->next == nullptr)
    {
        return llist;
    }
    
    //! Node for preserving original next node
    auto* orig_next = llist;
    
    while (orig_next->next != nullptr)
    {
        //! Update orig_next
        orig_next = orig_next->next;
        
        //! Swap prev and next
        std::swap(llist->prev, llist->next);
        
        //! Advance llist forwards
        llist = llist->prev;
    }
    
    //! Swap prev and next of final node in list
    std::swap(llist->prev, llist->next);
    
    return llist;

} // static DoublyLinkedListNode* reverse( ...

// Test case 0
TEST(ReverseTest, TestCase0) {
    DoublyLinkedList llist {};
    llist.insert_node(1);
    llist.insert_node(2);
    llist.insert_node(3);
    llist.insert_node(4);

    auto*      result_head = reverse(llist.head);
    const auto result_data = DoublyLinkedList::print(result_head);

    const std::vector<int> expected_data {4, 3, 2, 1};

    EXPECT_TRUE(std::equal(expected_data.cbegin(),
                           expected_data.cend(),
                           result_data.cbegin()));
}

// Test case 1
TEST(ReverseTest, TestCase1) {
    DoublyLinkedList llist {};
    llist.insert_node(2);
    llist.insert_node(3);
    llist.insert_node(4);

    auto*      result_head = reverse(llist.head);
    const auto result_data = DoublyLinkedList::print(result_head);

    const std::vector<int> expected_data {4, 3, 2};

    EXPECT_TRUE(std::equal(expected_data.cbegin(),
                           expected_data.cend(),
                           result_data.cbegin()));
}

// Test case 7
TEST(ReverseTest, TestCase7) {
    DoublyLinkedList llist {};
    llist.insert_node(17);
    llist.insert_node(20);
    llist.insert_node(23);
    llist.insert_node(35);
    llist.insert_node(47);

    auto*      result_head = reverse(llist.head);
    const auto result_data = DoublyLinkedList::print(result_head);

    const std::vector<int> expected_data {47, 35, 23, 20, 17};

    EXPECT_TRUE(std::equal(expected_data.cbegin(),
                           expected_data.cend(),
                           result_data.cbegin()));
}