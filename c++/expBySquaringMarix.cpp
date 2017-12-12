// Exp Squaring Algorithm
#include <iostream>

// assign n to all elements in the matrix
void all(int x[2][2], int n) {
    x[0][0] = n; x[0][1] = n;
    x[1][0] = n; x[1][1] = n;
}

// multiple matrix itself
void multiply(int x[2][2]) {
    int tmp[2][2];

    tmp[0][0] = x[0][0]*x[0][0] + x[0][1]*x[1][0];
    tmp[0][1] = x[0][0]*x[0][1] + x[0][1]*x[1][1];
    tmp[1][0] = x[0][0]*x[1][0] + x[1][0]*x[1][1];
    tmp[1][1] = x[0][1]*x[1][0] + x[1][1]*x[1][1];

    x[0][0] = tmp[0][0];
    x[0][1] = tmp[0][1];
    x[1][0] = tmp[1][0];
    x[1][1] = tmp[1][1];
}

void multiply(int x[2][2], int y[2][2]) {
    int tmp[2][2];
    
    tmp[0][0] = x[0][0]*y[0][0] + x[0][1]*y[1][0];
    tmp[0][1] = x[0][0]*y[0][1] + x[0][1]*y[1][1];
    tmp[1][0] = x[1][0]*y[0][0] + x[1][1]*y[1][0];
    tmp[1][1] = x[1][0]*y[0][1] + x[1][1]*y[1][1];

    y[0][0] = tmp[0][0];
    y[0][1] = tmp[0][1];
    y[1][0] = tmp[1][0];
    y[1][1] = tmp[1][1];
}

void expBySquaring(int x[2][2], int n) {
    if (n < 0) { return; }
    else if (n == 0) {
        all(x, 1);
        return;
    }

    int y[2][2];
    all(y, 1);

    while (n > 1) {
        if (n % 2 == 0) {
            multiply(x);
            n /= 2;
        } else {
            multiply(x, y);
            multiply(x);
            n = (n-1)/2;
        }
    }

    multiply(x, y);

    x[0][0] = y[0][0];
    x[0][1] = y[0][1];
    x[1][0] = y[1][0];
    x[1][1] = y[1][1];
    
    return;
}

int fib(int n) {
    int x[2][2] = {{1, 1}, {1, 0}};
    if (n == 0) { return 0;}
    else {
        expBySquaring(x, n-2);
    }
    return x[0][0];
}

void printResult(int n, int (*fun)(int n)) {
    printf("Input : %d\n", n);
    printf("Ouput : %d\n", fun(n));
}

int main(void) {
    int i = 100000;
    printResult(i, fib);
    return 0;
}



    
