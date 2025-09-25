/*
LeetCode 622: Design Circular Queue

Implement a fixed capacity circular queue supporting O(1) operations:
    - MyCircularQueue(k): construct queue of capacity k
    - enQueue(value): push value at the logical rear (fails if full)
    - deQueue(): pop from logical front (fails if empty)
    - Front()/Rear(): peek front / rear (return -1 if empty)
    - isEmpty()/isFull(): state queries

Core Idea (Ring Buffer):
We reuse a fixed-size vector and wrap indices with modulo arithmetic so that
no data needs to be physically shifted when elements are enqueued/dequeued.

State Invariants:
    - 0 <= count <= capacity
    - When count > 0, head indexes the current front element
    - When count > 0, tail indexes the current rear element
    - tail advances (tail + 1) % capacity on successful enqueue
    - head advances (head + 1) % capacity on successful dequeue
    - We initialize tail = -1 so first enqueue sets tail = 0 cleanly

Complexity:
    Time: O(1) for all operations
    Space: O(k)

Possible Alternatives:
    - Omit `tail` and compute as (head + count - 1) % capacity when needed.
    - Use capacity+1 storage and detect full by (tail+1)%N == head (sentinel slot).
*/

#include <vector>
using namespace std;

class MyCircularQueue {
private:
    vector<int> q;    // underlying fixed-size storage for elements
    int head;         // index of logical front element (valid if count > 0)
    int tail;         // index of logical rear element (valid if count > 0)
    int count;        // number of stored elements currently in queue
    int capacity;     // maximum number of elements queue can hold

public:
    explicit MyCircularQueue(int k)
        : q(k), head(0), tail(-1), count(0), capacity(k) {
        // vector pre-sized to capacity; contents uninitialized logically
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;          // cannot insert if already full
        tail = (tail + 1) % capacity;        // wrap tail forward circularly
        q[tail] = value;                     // store new element
        if (count == 0) {
            head = tail;                     // first element: head == tail
        }
        ++count;                             // update size
        return true;                         // success
    }
    
    bool deQueue() {
        if (isEmpty()) return false;         // nothing to remove
        head = (head + 1) % capacity;        // logically discard front
        --count;                             // decrease element count
        if (count == 0) {                    // queue became empty
            // Optional reset to initial state (not required for correctness)
            head = 0;                        // keeps indices tidy
            tail = -1;
        }
        return true;                         // success
    }
    
    int Front() const {
        return isEmpty() ? -1 : q[head];     // return element or sentinel
    }
    
    int Rear() const {
        return isEmpty() ? -1 : q[tail];     // return element or sentinel
    }
    
    bool isEmpty() const {                   // true if no stored elements
        return count == 0;
    }
    
    bool isFull() const {                    // true if size reached capacity
        return count == capacity;
    }

    int size() const {                       // helper: current number of elements
        return count;
    }
};
