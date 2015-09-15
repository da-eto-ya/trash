#include <iostream>

int main() {
    char c = '\0';

    while (std::cin) {
        while (std::cin.get(c)) {
            std::cout << c;

            if (' ' == c) {
                break;
            }
        }

        while (std::cin.get(c)) {
            if (' ' != c) {
                std::cout << c;
                break;
            }
        }
    }

    return 0;
}