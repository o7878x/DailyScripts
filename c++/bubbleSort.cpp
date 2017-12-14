// C++ program for implementation of Bubble sort
#include <iostream>

// assistance function
void swap(int *px, int *py) {
    int temp = *px;
    *px = *py;
    *py = temp;
}

// hyper assistance function
void swapEx(int *px, int *py) {
    *px = *px ^ *py;
    *py = *px ^ *py;
    *px = *px ^ *py;
}

// Simplest way to implement bubble sort
// Always run O(n^2) time even if the array is sorted
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Optimized implementation
// It can be optimized by stopping the algorithm if inner loop didn't cause any swap
// Worst and Average Case Time Complexity: O(n^2)
// Best Case Time Complexity: O(n)
// Auxiliary Space: O(1)
// Sorting in place: yes
// Stable: yes

void bubbleSortEx(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        bool isSwap = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swapEx(&arr[j], &arr[j+1]);
                isSwap = true;
            }
        }
        if (!isSwap) { break; }
    }
}


/* Function to print an array */
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Dirver program to tset above functions
int main(void) {
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n = sizeof(arr)/sizeof(arr[0]);
    bubbleSortEx(arr, n);
    printArray(arr, n);
    return 0;
}
