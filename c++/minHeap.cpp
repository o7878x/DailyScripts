#include <iostream>
#include <climits>
using namespace std;

// Prototype of a utility function to swap two integers
void swap(int *x, int *y);

// A class for Min Heap
class MinHeap {
    int *harr;
    int capacity;
    int heap_size;
public:
    MinHeap(int capacity);

    void MinHeapify();

    int parent(int i) { return (i-1)/2; }

    int left(int i) { return (2*i+1); }

    int right(int i) { return (2*i+2); }

    int extractMin();

    void decreaseKey(int i, int new_val);

    int getMin() { return harr[0]; }

    void deleteKey(int i);

    void insertKey(int k);

};

MinHeap::MinHeap(int cap) {
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}


