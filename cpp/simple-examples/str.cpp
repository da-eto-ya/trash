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

    struct StringSlice;

    StringSlice operator[](size_t from) const;

    size_t size;
    char *str;
};

struct String::StringSlice {
    StringSlice(size_t from, const String &source) : from(from), size(source.size - from), str(new char[size + 1]) {
        for (size_t i = 0; i < size; ++i) {
            str[i] = source.str[from + i];
        }

        str[size] = '\0';
    }

    ~StringSlice() {
        delete[] str;
    }

    String operator[](size_t to) const {
        str[to - from] = '\0';

        return String(str);
    }

    size_t from;
    size_t size;
    char *str;
};

String::StringSlice String::operator[](size_t from) const {
    return StringSlice(from, *this);
}

int main() {
    String hello("hello");
    hello.append(", world");

    const String hell = hello[0][4];
    std::cout << hell.str << std::endl;
}
