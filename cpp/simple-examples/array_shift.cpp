#include <iostream>

#define N 10

void reverse(int *first, int *last) {
    for (--last; first < last; ++first, --last) {
        *first ^= *last;
        *last ^= *first;
        *first ^= *last;
    }
}

void rotate(int a[], unsigned size, int shift) {
    shift = shift >= 0 ? shift % size : size - shift % size;
    reverse(a, a + shift);
    reverse(a + shift, a + size);
    reverse(a, a + size);
}

int main() {
    int a[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    rotate(a, N, -3);

    for (int i = 0; i < N; ++i) {
        std::cout << a[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}