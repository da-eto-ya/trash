#include <iostream>
#include <cstring>
#include <algorithm>

struct String {
    String(const char *str = "") : size(strlen(str)), str(new char[size + 1]) {
        std::copy(str, str + size + 1, this->str);
    }

    String(size_t n, char c) : size(n), str(new char[size + 1]) {
        std::fill(str, str + size, c);
        str[size] = '\0';
    }

    ~String() {
        delete[] str;
    }

    String(const String &other) : size(other.size), str(new char[size + 1]) {
        std::copy(other.str, other.str + size + 1, str);
    }

    void swap(String &other) {
        std::swap(size, other.size);
        std::swap(str, other.str);
    }

    String &operator=(const String &other) {
        if (this != &other) {
            String(other).swap(*this);
        }

        return *this;
    }

    void append(const String &other) {
        char *buf = new char[size + other.size + 1];

        std::copy(str, str + size, buf);
        std::copy(other.str, other.str + other.size, buf + size);
        buf[size + other.size] = '\0';

        delete[] str;
        str = buf;
        size += other.size;
    }

    size_t size;
    char *str;
};

int main() {
    String s("Hello");
    s.append(", world");
    std::cout << s.str << std::endl;
}
