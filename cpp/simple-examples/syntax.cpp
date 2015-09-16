#include <iostream>

using namespace std;

#define MAX(x, y, r)    { int ___x = (x); int ___y = (y); r = ___x > ___y ? ___x : ___y; }

int power(int x, unsigned p) {
    int answer = 1;

    for (int i = 0; i < p; ++i) {
        answer *= x;
    }

    return answer;
}

int main() {
    cout << power(10, 4) << endl;

    int a = 10;
    int b = 20;
    int c = 0;
    MAX(a, b, c);
    cout << c << endl;

    return 0;
}
