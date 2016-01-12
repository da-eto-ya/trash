#include <iostream>

#include <map>
#include <sstream>

std::string derivative(std::string polynomial) {
    std::string poly(polynomial);
    poly.push_back('+');
    std::map<int, int, std::greater<int>> res;

    char state = 's';
    int sign = 1;
    int coefficient = 0;
    int power = 0;

    for (auto ch : poly) {
        switch (state) {
            case 's':
                if ('+' == ch || '-' == ch) {
                    sign = '-' == ch ? -1 : 1;
                } else if ('0' <= ch && ch <= '9') {
                    coefficient = ch - '0';
                    state = 'c';
                } else if ('x' == ch) {
                    coefficient = sign;
                    state = 'l';
                } else {
                    state = 'e';
                }
                break;

            case 'c':
                if ('0' <= ch && ch <= '9') {
                    coefficient = coefficient * 10 + ch - '0';
                } else if ('*' == ch) {
                    coefficient = sign * coefficient;
                    state = 'l';
                } else if ('+' == ch || '-' == ch) {
                    coefficient = sign * coefficient;
                    sign = '-' == ch ? -1 : 1;
                    state = 's';

                    res[power] += coefficient;

                    coefficient = 0;
                    power = 0;
                }
                break;

            case 'l':
                if ('x' == ch || '*' == ch) {
                    state = 'l';
                } else if ('^' == ch) {
                    power = 0;
                    state = 'p';
                } else if ('+' == ch || '-' == ch) {
                    sign = '-' == ch ? -1 : 1;
                    state = 's';
                    power = 1;

                    res[power] += coefficient;

                    coefficient = 0;
                    power = 0;
                }
                break;

            case 'p':
                if ('0' <= ch && ch <= '9') {
                    power = power * 10 + ch - '0';
                } else if ('+' == ch || '-' == ch) {
                    sign = '-' == ch ? -1 : 1;
                    state = 's';

                    res[power] += coefficient;

                    coefficient = 0;
                    power = 0;
                }
                break;

            case 'e':
                break;

            default:
                break;
        }
    }

    std::ostringstream oss;
    bool first_element = true;

    for (auto r : res) {
        coefficient = r.second * r.first;
        power = r.first - 1;

        if (power >= 0) {
            if (!first_element && coefficient > 0) {
                oss << "+";
            }

            oss << coefficient;
        }

        switch (power) {
            case -1:
                if (first_element) {
                    oss << coefficient;
                }

                break;

            case 0:
                break;

            case 1:
                oss << "*x";
                break;

            default:
                oss << "*x^" << power;
                break;
        }

        first_element = false;
    }

    return oss.str();
}

int main() {
    std::string s;
    std::cin >> s;
    std::cout << derivative(s) << std::endl;
    return 0;
}