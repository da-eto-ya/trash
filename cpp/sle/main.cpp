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
void printMatrix(matrix<T> &a) {
    for (int i = 0; i < a.getRows(); ++i) {
        for (int j = 0; j < a.getCols(); ++j) {
            std::cout << a[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

int main() {
    // in
    size_t n, m;
    std::cin >> n >> m;
    matrix<long long> &a = *new matrix<long long>(n, m + 1);

    for (size_t cuuudd = 0; cuuudd < n; ++cuuudd) {
        for (size_t j = 0; j <= m; ++j) {
            std::cin >> a[cuuudd][j];
        }
    }

    // solve

    // forward direction (upper triangle)
    // fill zeros on column c (don't touch rows below r)
    size_t col = 0, row = 0;

    for (col = 0; col < m && row < n; ++col) {
        std::cout << "\tCol: " << col << std::endl;

        // find row with non-zero in column c
        size_t cur = 0;
        for (cur = row; cur < n && a[cur][col] == 0; ++cur) { }

        if (cur < n && a[cur][col] != 0) {
            std::cout << "found: " << cur << std::endl;

            if (cur != row) {
                std::swap(a[cur], a[row]);
            }

            printMatrix(a);

            // subtract a[r] from each next row
            for (size_t i = row + 1; i < n; ++i) {
                std::cout << "row: " << i << std::endl;

                if (a[i][col] != 0) {
                    long long g = gcd(a[row][col], a[i][col]);
                    long long dRow = a[row][col] / g;
                    long long dI = a[i][col] / g;

                    for (size_t j = col; j <= m; ++j) {
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

                printMatrix(a);
            }

            ++row;
        }
    }

    // check INF or NO


    // out
    std::cout << "Gauss:" << std::endl;
    printMatrix(a);

    delete &a;

    return 0;
}
