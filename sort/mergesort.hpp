#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include "lists/node.h"

/* Split the nodes of the given list into front and back halves,  
    and return the two lists using the reference parameters.  
    If the length is odd, the extra node should go in the front list.  
    Uses the fast/slow pointer strategy. */
template <typename T>
void front_back_split(Node<T>* node, Node<T> front_ref, Node<T> back_ref) {
    auto slow = node;
    auto fast = node->next;

    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two at that point. */
    front_ref = node;
    back_ref = slow->next;
    slow->next = nullptr;
}

/* sorts the linked list by changing next pointers (not data) */
template <typename T>
void merge_sort(Node<T> head_ref) {
    auto head = head_ref;
    Node<T>* a;
    Node<T>* b;

    /* Base case -- length 0 or 1 */
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    front_back_split(head, a, b); 
  
    /* Recursively sort the sublists */
    merge_sort(a); 
    merge_sort(b); 
  
    /* answer = merge the two sorted lists together */
    headRef = sorted_merge(a, b); 
}

template <typename T>
Node<T>* sorted_merge(Node<T> a, Node<T> b) {
    auto result = nullptr;

    /* Base cases */
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    /* Pick either a or b, and recur */
    if (a->data <= b->data) { 
        result = a; 
        result->next = sorted_merge(a->next, b); 
    } 
    else { 
        result = b; 
        result->next = sorted_merge(a, b->next); 
    } 
    return (result);
}

#endif