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

// Dynamic planning method
int eggDropEx(int n, int k) {
    /* A 2D table where entry eggFloor[i][j] will represent minimum number of n eggs and k floors */
    int eggFloor[n+1][k+1];

    // boundary condition
    for (int i = 1; i <= n; i++) {
        eggFloor[i][0] = 0;
        eggFloor[i][1] = 1;
    }

    for (int j = 1; j <= k; j++) {
        eggFloor[1][j] = j;
    }

    // Fill rest of the entries in table using optimal substructure property
    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            eggFloor[i][j] = INT_MAX;
            for (int x = 1; x <= j; x++) {
                int res = 1 + max(eggFloor[i-1][x-1] , eggFloor[i][j-x]);
                if (res < eggFloor[i][j]) {
                    eggFloor[i][j] = res;
                }
            }
        }
    }

    return eggFloor[n][k];
}


int main(void) {
    int n = 2, k = 100;
    printf("\nMinimum number of trials in worst case with %d eggs and %d floors is %d\n", n, k, eggDropEx(n, k));
    return 0;
}
