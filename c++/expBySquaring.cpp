// Reference: https://en.wikipedia.org/wiki/Exponentiation_by_squaring
#include <iostream>

// Recursive version
double expBySquaring1(double x, int n) {
    if (n == 0) { return 1; }
    else if (n == 1) { return x; }
    else if (n < 0) { return expBySquaring1(1/x, -n); }
    else if (n % 2 == 0) { return expBySquaring1(x*x, n/2); }
    else { return x * expBySquaring1(x*x, (n-1)/2); }
}

// Tail Recursive version
double expBySquaring2Core(double y, double x, int n) {
    if (n == 0) { return y; }
    else if (n == 1) { return y * x; }
    else if (n < 1) { return expBySquaring2Core(y, 1/x, -n); }
    else if (n % 2 == 0) { return expBySquaring2Core(y, x*x, n/2); }
    else { return expBySquaring2Core(y*x, x*x, (n-1)/2); }
}

double expBySquaring2(double x, int n) {
    return expBySquaring2Core(1, x, n);
}

// Iterative version
double expBySquaring3(double x, int n) {
    if (n == 0) { return 1; }
    if (n < 0) {
        x = 1/x;
        n = -n;
    }

    double y=1;
    while (n > 1) {
        if (n%2 == 0) {
            x = x * x;
            n /= 2;
        } else {
            y = x * y;
            x = x * x;
            n = (n-1)/2;
        }
    }

    return x * y;
}

void printResult(double x, int n, double (*fun)(double x, int n)) {
    printf("Intput: %f, %d\n", x, n);
    printf("Output: %f\n", fun(x, n));
}

int main(void) {
    double x = 2.0;
    int n = 10;
    printResult(x, n, expBySquaring1);
    printResult(x, n, expBySquaring2);
    printResult(x, n, expBySquaring3);
    return 0;
}
