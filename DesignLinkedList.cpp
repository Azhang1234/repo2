/*
LeetCode 707: Design Linked List

Design your implementation of the linked list. 
Implement methods:
- get(index): Get the value of the index-th node.
- addAtHead(val): Insert at head.
- addAtTail(val): Append at tail.
- addAtIndex(index, val): Insert at index.
- deleteAtIndex(index): Delete the index-th node.
*/

#include <iostream>
using namespace std;

class MyLinkedList {
private:
    struct Node {
        int val;
        Node* next;
        Node(int v): val(v), next(nullptr) {}
    };
    Node* head;
    int size;
    
public:
    MyLinkedList() {
        head = nullptr;
        size = 0;
    }
    
    int get(int index) {
        if (index < 0 || index >= size) return -1;
        Node* cur = head;
        for (int i = 0; i < index; i++) cur = cur->next;
        return cur->val;
    }
    
    void addAtHead(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
        size++;
    }
    
    void addAtTail(int val) {
        Node* node = new Node(val);
        if (!head) {
            head = node;
        } else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = node;
        }
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) return;
        if (index == 0) {
            addAtHead(val);
            return;
        }
        Node* cur = head;
        for (int i = 0; i < index - 1; i++) cur = cur->next;
        Node* node = new Node(val);
        node->next = cur->next;
        cur->next = node;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        if (index == 0) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        } else {
            Node* cur = head;
            for (int i = 0; i < index - 1; i++) cur = cur->next;
            Node* tmp = cur->next;
            cur->next = cur->next->next;
            delete tmp;
        }
        size--;
    }
};
