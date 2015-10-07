#include <iostream>
#include <vector>

bool next_perm(std::vector<int> &a, int n) {
    int k = (int) a.size();

    for (int i = k - 1; i >= 0; --i){
        if (a[i] < n - k + i + 1) {
            ++a[i];

            for (int j = i + 1; j < k; ++j) {
                a[j] = a[j - 1] + 1;
            }

            return true;
        }
    }

    return false;
}


int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<int> a;
    a.resize(k);

    for (int i = 0; i < k; ++i) {
        a[i] = i + 1;
    }

    do {
        for (int i = 0; i < k; ++i) {
            std::cout << a[i] - 1 << " ";
        }

        std::cout << std::endl;
    } while (next_perm(a, n));

    return 0;
}
