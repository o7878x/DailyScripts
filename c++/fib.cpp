// Fibonacci Series using different algorithm
#include <iostream>

// Recursion Version
// Time Complexity: T(n) = T(n-1) + T(n-2)
// Extra Space: O(n)
int fib1(int n) {
    return n <= 1 ? n : fib1(n-1) + fib1(n-2);
}


// Dynamic Planning (Not Space Optimized Method)
// Time Complexity: O(n)
// Extra Space: O(n)
int fib2(int n) {
    if (n <= 1) { return n; }

    int fib[n+1];

    fib[0] = 0;
    fib[1] = 1;

    for (int i = 2; i <= n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }

    return fib[n];
}

// Dynamic Planning (Space Optimized Method)
// Time Complexity: O(n)
// Extra Space: O(1)
int fib3(int n) {
    if (n <= 1) { return n; }

    int n0 = 0;
    int n1 = 1;
    int n2;

    for (int i = 2; i <= n; i++) {
        n2 = n0 + n1;
        n0 = n1;
        n1 = n2;
    }

    return n2;
}


void printResult(int n, int (*fun)(int n)) {
    printf("Input : n = %d\n", n);
    printf("Output : %d\n", fun(n));
}

int main(void) {
    //printResult(9, fib1);
    //printResult(9, fib2);
    int i = 100000;
    printResult(i, fib3);
    return 0;
}
