#include <iostream>
#include <vector>

int main() {
    long long n;
    int m;
    std::cin >> n >> m;
    std::vector<int> fib;
    fib.push_back(0);
    fib.push_back(1);

    for (long long i = 2; i <= n; ++i) {
        fib.push_back((fib[i - 1] + fib[i - 2]) % m);

        if (fib[i] == 1 && fib[i - 1] == 0) {
            break;
        }
    }

    int result;

    if (fib.size() > n) {
        result = fib[n];
    } else {
        result = fib[n % (fib.size() - 2)];
    }

    std::cout << result << std::endl;

    return 0;
}