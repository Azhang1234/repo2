/*
LeetCode 622: Design Circular Queue

Design your implementation of the circular queue. 
Implement the MyCircularQueue class:

MyCircularQueue(k): Initializes the queue with the size k.
enQueue(value): Inserts an element into the circular queue. Return true if the operation is successful.
deQueue(): Deletes an element from the circular queue. Return true if the operation is successful.
Front(): Gets the front item. If empty, return -1.
Rear(): Gets the last item. If empty, return -1.
isEmpty(): Checks whether the queue is empty.
isFull(): Checks whether the queue is full.
*/

#include <vector>
using namespace std;

class MyCircularQueue {
private:
    vector<int> q;   // internal array
    int head, tail;  // indices
    int count;       // current size
    int capacity;    // max size

public:
    MyCircularQueue(int k) {
        capacity = k;
        q.resize(k);
        head = 0;
        tail = -1;
        count = 0;
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;
        tail = (tail + 1) % capacity; // circular increment
        q[tail] = value;
        count++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        head = (head + 1) % capacity; // move head forward
        count--;
        return true;
    }
    
    int Front() {
        return isEmpty() ? -1 : q[head];
    }
    
    int Rear() {
        return isEmpty() ? -1 : q[tail];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
};
