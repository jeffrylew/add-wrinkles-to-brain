#include "singly_linked_list.hpp"

#include <gtest/gtest.h>

#include <cstdlib>
#include <unordered_set>

static int findMergeNode(SinglyLinkedListNode* head1,
                         SinglyLinkedListNode* head2)
{
    //! Set for storing memory locations of nodes in both lists
    std::unordered_set<SinglyLinkedListNode*> node_set {};

    while (head1 != nullptr)
    {
        //! Attempt to copy current head1 into set
        if (not node_set.insert(head1).second)
        {
            //! Node was already added to set so this is the merge node
            return head1->data;
        }
        
        head1 = head1->next;
    }
    
    while (head2 != nullptr)
    {
        //! Attempt to copy current head2 into set
        if (not node_set.insert(head2).second)
        {
            //! Node was already added to set so this is the merge node
            return head2->data;
        }
        
        head2 = head2->next;
    }
    
    //! If this point is reached, all nodes in one or both of the lists
    //! have been exhausted. There is no merge node in this situation
    //! but the problem states "The lists will merge" so this won't be
    //! reached. Just return an arbitrary value of 0
    return 0;

} // static int findMergeNode( ...

// Test case 0
TEST(FindMergeNodeTest, TestCase0) {
    // Initialize SinglyLinkedLists
    SinglyLinkedList* llist1 = new SinglyLinkedList();
    llist1->insert_node(1);
    llist1->insert_node(2);
    llist1->insert_node(3);

    SinglyLinkedList* llist2 = new SinglyLinkedList();
    llist2->insert_node(1);
    
    // Set merge node in llist2
    llist2->head->next = llist1->head->next;

    EXPECT_EQ(2, findMergeNode(llist1->head, llist2->head));

    // Free allocated memory (manually handle llist2 to avoid double free)
    free_singly_linked_list(llist1->head);
    std::free(llist2->head);
}

// Test case 1
TEST(FindMergeNodeTest, TestCase1) {
    // Initialize SinglyLinkedLists
    SinglyLinkedList* llist1 = new SinglyLinkedList();
    llist1->insert_node(1);
    llist1->insert_node(2);
    llist1->insert_node(3);

    SinglyLinkedList* llist2 = new SinglyLinkedList();
    llist2->insert_node(1);
    
    // Set merge node in llist2
    llist2->head->next = llist1->head->next->next;

    EXPECT_EQ(3, findMergeNode(llist1->head, llist2->head));

    // Free allocated memory (manually handle llist2 to avoid double free)
    free_singly_linked_list(llist1->head);
    std::free(llist2->head);
}