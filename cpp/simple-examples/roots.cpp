#include <iostream>
#include <cmath>

int main() {
    int a, b, c;
    std::cin >> a >> b >> c;
    double det = b * b - 4 * a * c;

    if (det >= 0) {
        std::cout << (-b - sqrt(det)) / (2.0 * a) << " " << (-b + sqrt(det)) / (2.0 * a) << std::endl;
    } else {
        std::cout << "No real roots" << std::endl;
    }

    return 0;
}