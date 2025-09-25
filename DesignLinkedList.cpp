/*
LeetCode 707: Design Linked List

Goal: Implement a singly linked list supporting the following operations.
    - get(index): Return value at index (0-based) or -1 if invalid
    - addAtHead(val): Insert new node at front
    - addAtTail(val): Append new node at end
    - addAtIndex(index,val): Insert before node currently at position index
                * if index == size => append
                * if index > size or index < 0 => no-op
    - deleteAtIndex(index): Remove node at index if valid

Design Enhancements Added:
    - Sentinel (dummy) head node: simplifies insert/delete at head (no special case logic)
    - Tail pointer: enables O(1) addAtTail (instead of O(n) traversal)
    - Stored size: O(1) length access and bounds validation
    - Destructor to free all allocated nodes

Complexities:
    get: O(min(index, size-index)) if doubly linked; here singly so O(index)
    addAtHead / addAtTail: O(1)
    addAtIndex: O(index) traversal
    deleteAtIndex: O(index)
    Space: O(n)

Possible Further Improvements:
    - Convert to doubly linked for potential bidirectional optimizations
    - Add iterator support
*/

// Only need <cstddef> for nullptr and basic types; <iostream> removed.
#include <cstddef>
using namespace std; // (Kept for consistency; remove in larger projects.)

class MyLinkedList {
private:
    struct Node {            // basic singly linked list node
        int val;             // stored value
        Node* next;          // pointer to next node
        Node(int v): val(v), next(nullptr) {}
    };
    Node* sentinel;          // dummy head (never holds user data)
    Node* tail;              // pointer to last REAL node (or sentinel if empty)
    int length;              // number of actual data nodes
    
public:
    MyLinkedList()
        : sentinel(new Node(0)), tail(sentinel), length(0) {
        // Initially list is empty: sentinel->next == nullptr, tail == sentinel
    }

    ~MyLinkedList() {
        // Delete all nodes including sentinel
        Node* cur = sentinel;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }
    
    int get(int index) const {
        if (index < 0 || index >= length) return -1; // bounds check
        Node* cur = sentinel->next;                  // first data node
        for (int i = 0; i < index; ++i)
            cur = cur->next;
        return cur->val;                             // value at index
    }
    
    void addAtHead(int val) {
        Node* node = new Node(val);          // allocate new node
        node->next = sentinel->next;         // link new node before current first
        sentinel->next = node;               // sentinel now points to new first
        if (tail == sentinel)                // list was previously empty
            tail = node;                     // update tail to the single node
        ++length;                            // increment length
    }
    
    void addAtTail(int val) {
        Node* node = new Node(val);          // allocate
        tail->next = node;                   // append after current tail (sentinel if empty)
        tail = node;                         // update tail pointer
        ++length;                            // size++
    }
    
    void addAtIndex(int index, int val) {
        if (index < 0 || index > length) return; // invalid index guard
        if (index == 0) {                        // insert at head
            addAtHead(val);
            return;
        }
        if (index == length) {                   // append
            addAtTail(val);
            return;
        }
        // Traverse to node BEFORE insertion site
        Node* prev = sentinel->next;             // first data node
        for (int i = 0; i < index - 1; ++i)
            prev = prev->next;
        Node* node = new Node(val);              // create new node
        node->next = prev->next;                 // link to successor
        prev->next = node;                       // link predecessor to new node
        ++length;                                // update length
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index >= length) return; // invalid index
        // find node BEFORE the one to delete
        Node* prev = sentinel;                     // start at sentinel simplifies deletion
        for (int i = 0; i < index; ++i)
            prev = prev->next;
        Node* target = prev->next;                 // node to remove
        prev->next = target->next;                 // unlink target
        if (target == tail)                        // if removing last node
            tail = prev;                           // update tail pointer
        delete target;                             // free memory
        --length;                                  // decrement length
    }

    int size() const { return length; }            // helper accessor
};
