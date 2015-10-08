#include <iostream>

long long lcm(long long a, long long b) {
    long long p = a * b;

    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }

    p /= a;

    return p;
}

int find_not_in_cycle(bool *b, int n) {
    for (int i = 0; i < n; ++i) {
        if (!b[i]) {
            return i;
        }
    }

    return -1;
}

int main() {
    int n;
    std::cin >> n;
    int *a = new int[n];
    bool *b = new bool[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        --a[i];
        b[i] = false;
    }

    int c;
    long long p = 1;

    while ((c = find_not_in_cycle(b, n)) != -1) {
        int len = 0;
        int d = c;

        do {
            d = a[d];
            b[d] = true;
            ++len;
        } while (d != c);

        p = lcm(p, len);
    }

    std::cout << p << std::endl;

    return 0;
}
