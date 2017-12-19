#include <cstdio>
#include <cmath>

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

void insertionSortRe(int arr[], int n) {
    int key, i, j;
    for (i = n-2; i >= 0; i--) {
        key = arr[i];
        for (j = i+1; j < n && arr[j] < key; j++) {
            arr[j-1] = arr[j];
        }
        arr[j-1] = key;
    }
}

void printResult(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int n = sizeof(arr)/sizeof(arr[0]);
    insertionSortRe(arr, n);
    printResult(arr, n);

    return 0;
}
