#include <iostream>

int intlog(int a) {
    int res = 0;

    while (a > 1) {
        a /= 2;
        ++res;
    }

    return res;
}

int main() {
    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        int a;
        std::cin >> a;
        std::cout << intlog(a) << std::endl;
    }

    return 0;
}