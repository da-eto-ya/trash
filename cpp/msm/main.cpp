#include <iostream>
#include <vector>
#include <cmath>

#define EPSILON 0.00000001

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

    size_t getRows() const {
        return rows;
    }

    size_t getCols() const {
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
void gaussify(matrix<T> &a) {
    size_t n = a.getRows();
    size_t m = a.getCols() - 1;
    size_t row = 0;
    size_t col = 0;

    for (col = 0; col < m && row < n; ++col) {
        // find row with non-zero in column c
        size_t cur = 0;
        for (cur = row; cur < n && fabs(a[cur][col]) < EPSILON; ++cur) { }

        if (cur < n && a[cur][col] != 0) {
            if (cur != row) {
                std::swap(a[cur], a[row]);
            }

            // subtract a[r] from each next row
            for (size_t i = row + 1; i < n; ++i) {
                if (a[i][col] != 0) {
                    double dRow = a[row][col];
                    double dI = a[i][col];

                    a[i][col] = 0;

                    for (size_t j = col + 1; j <= m; ++j) {
                        a[i][j] = a[i][j] * dRow - a[row][j] * dI;
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
            double dRow = a[row][row];
            double dI = a[i][row];

            for (size_t j = i; j < a.getCols(); ++j) {
                a[i][j] = a[i][j] * dRow - a[row][j] * dI;
            }
        }
    }
}

double scalarProd(const matrix &m, size_t a, size_t b) {
    double sum = 0;

    for (size_t i = 0; i < m.getRows(); ++i) {
        sum += m[i][a] * m[i][b];
    }

    return sum;
}

int main() {
    // in
    size_t n, m;
    std::cin >> n >> m;
    matrix<double > a(n, m + 1);

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j <= m; ++j) {
            std::cin >> a[i][j];
        }
    }

    matrix<double > b(m, m+1);

    for (size_t i = 0; i < m; ++i) {
        
    }

    // solve
    gaussify(b);
    diagonalize(b);

    return 0;
}
