#include <stdio.h>

int fib(int a) {
    if (a <= 0) {
        return 0;
    }

    if (a == 1 || a == 2) {
        return 1;
    }

    return fib(a - 1) + fib(a - 2);
}

int main() {
    printf("%d", fib(5));

    return 0;
}
