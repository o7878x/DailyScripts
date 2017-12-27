#include <cstdio>

using namespace std;

int getSingle(int arr[], int n) {
    int ones = 0, twos = 0;
    int common_bit_mask;

    // Let us take the expmale of {3, 3, 2, 3} to understand this
    for (int i = 0; i < n; i++) {
        /* The expression "one & arr[i]" gives the bits are there in both 'ones' and new element from arr[]. We add these bits to 'twos' using bitwise OR
         * Value of 'twos' will be set as 0, 3, 3 and 1 after 1st, 2nd, 3rd and 4th iterations respectively
         */
        twos = twos | (ones & arr[i]);

        /* XOR the new bits with previsou 'ones' to get all bits
         * appearing odd number of times 
