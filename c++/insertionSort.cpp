#include <cstdio>
#include <cmath>


/* Function to sort an array using insertion sort
 * Time Complexity: O(n*n)
 * Auxiliary Space: O(1)
 * Boundary Cases: Insertion sort takes maximum time to sort if elements are sortdd in reverse oder. And it takes minimum time (order of n) when elemnets are already sorted.
 */
void insertionSort(int arr[], int n) {
    int key, i, j;

    for (i = 1; i < n; i++) {
        key = arr[i];
        for (j = i-1; j >= 0 && arr[j] > key; j--) {
            arr[j+1] = arr[j];
        }
        arr[j+1] = key;
    }
}

// A utility function to print an array of size n
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* Driver program to test insertion sort */
int main(void) {
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr)/sizeof(arr[0]);

    insertionSort(arr, n);
    printArray(arr, n);

    return 0;
}
