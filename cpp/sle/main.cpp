#include <iostream>
#include <vector>

template<class T>
class matrix {
public:
    matrix<T>(size_t rows, size_t cols) : rows(rows), cols(cols) {
        storage.resize(rows);

        for (int i = 0; i < rows; ++i) {
            storage[i].resize(cols);
        }
    }

    virtual ~matrix<T>() { }

    size_t getRows() {
        return rows;
    }

    size_t getCols() {
        return cols;
    }

    std::vector<T> &operator[](size_t idx) {
        return storage[idx];
    }

private:
    std::vector<std::vector<T> > storage;
    size_t rows;
    size_t cols;
};

long long gcd(long long a, long long b) {
    long long c;

    while (0 != a) {
        c = a;
        a = b % a;
        b = c;
    }

    return b;
}

template<class T>
bool upperInconsistent(matrix<T> &a) {
    bool solvable = true;

    for (int i = 0; i < a.getRows() && solvable; ++i) {
        bool zeroed = true;

        for (int j = 0; j < a.getCols() - 1 && zeroed; ++j) {
            zeroed = (a[i][j] == 0);
        }

        if (zeroed) {
            solvable = (a[i][a.getCols() - 1] == 0);
        }
    }

    return !solvable;
}

template<class T>
bool upperOneSolution(matrix<T> &a) {
    size_t n = a.getCols() - 1;

    if (a.getRows() < n) {
        return false;
    }

    bool solvable = true;

    for (size_t i = 0; i < n && solvable; ++i) {
        solvable = (a[i][i] != 0);
    }

    for (size_t i = n; i < a.getRows() && solvable; ++i) {
        for (size_t j = 0; j < a.getCols() && solvable; ++j) {
            solvable = (a[i][j] == 0);
        }
    }

    return solvable;
}

template<class T>
void gaussify(matrix<T> &a) {
    size_t n = a.getRows();
    size_t m = a.getCols() - 1;
    size_t row = 0;
    size_t col = 0;

    for (col = 0; col < m && row < n; ++col) {
        // find row with non-zero in column c
        size_t cur = 0;
        for (cur = row; cur < n && a[cur][col] == 0; ++cur) { }

        if (cur < n && a[cur][col] != 0) {
            if (cur != row) {
                std::swap(a[cur], a[row]);
            }

            // subtract a[r] from each next row
            for (size_t i = row + 1; i < n; ++i) {
                if (a[i][col] != 0) {
                    long long g = gcd(a[row][col], a[i][col]);
                    long long dRow = a[row][col] / g;
                    long long dI = a[i][col] / g;

                    a[i][col] = 0;

                    for (size_t j = col + 1; j <= m; ++j) {
                        a[i][j] = a[i][j] * dRow - a[row][j] * dI;
                    }

                    // simplify line (divide by gcd)
                    long long gcdCurrent = 0;

                    for (size_t j = col + 1; j <= m && gcdCurrent != 1; ++j) {
                        gcdCurrent = gcd(gcdCurrent, a[i][j]);
                    }

                    if (gcdCurrent != 0 && gcdCurrent != 1) {
                        for (size_t j = col + 1; j <= m; ++j) {
                            a[i][j] /= gcdCurrent;
                        }
                    }
                }
            }

            ++row;
        }
    }
}

template<class T>
void diagonalize(matrix<T> &a) {
    size_t n = a.getCols() - 1;

    if (a.getRows() < n) {
        return;
    }

    for (size_t row = n - 1; row > 0; --row) {
        for (size_t i = 0; i < row; ++i) {
            long long g = gcd(a[row][row], a[i][row]);
            long long dRow = a[row][row] / g;
            long long dI = a[i][row] / g;

            for (size_t j = i; j < a.getCols(); ++j) {
                a[i][j] = a[i][j] * dRow - a[row][j] * dI;
            }
        }
    }
}

int main() {
    // in
    size_t n, m;
    std::cin >> n >> m;
    matrix<long long> &a = *new matrix<long long>(n, m + 1);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j <= m; ++j) {
            std::cin >> a[i][j];
        }
    }

    // solve
    gaussify(a);

    if (upperInconsistent(a)) {
        std::cout << "NO" << std::endl;
    } else if (upperOneSolution(a)) {
        diagonalize(a);
        std::cout << "YES" << std::endl;
        std::cout.precision(15);

        for (size_t i = 0; i < m; ++i) {
            std::cout << std::fixed << (a[i][m] * 1.0) / a[i][i] << " ";
        }

        std::cout << std::endl;
    } else {
        std::cout << "INF" << std::endl;
    }

    delete &a;

    return 0;
}
