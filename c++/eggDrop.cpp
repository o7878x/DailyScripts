// Egg Dropping Puzzle
#include <iostream>
#include <climits>

// A utility function to get maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }

/* Function to get minimum number of trials of needed to worst
 * case with n eggs and k floors */
int eggDrop(int n, int k) {
    // If there are no floor, then no trials needed.
    // Or if there are only one floor, then one trial neeed.
    if (k <= 1) { return k; }

    // If there is only one egg, then k trials needed
    if (n == 1) { return k; }

    // Consider all droppings from 1st floor to kth floor and
    // return the minimum of these values plus 1
    int min = INT_MAX;
    int tmp;
    for (int x = 1; x <= k; x++) {
        tmp = max(eggDrop(n-1, x-1), eggDrop(n, k-x));
        if (tmp < min) { min = tmp; }
    }
    return min+1;
}

int main(void) {
    int n = 2, k = 20;
    printf("\nMinimum number of trials in worst case with %d eggs and %d floors is %d\n", n, k, eggDrop(n, k));
    return 0;
}
