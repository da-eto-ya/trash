#include <iostream>

char *alloc_and_copy(char *buffer, size_t size, size_t newSize) {
    if (newSize != size) {
        char *newBuffer = new char[newSize];

        for (size_t i = 0, s = (size < newSize ? size : newSize); i < s; ++i) {
            newBuffer[i] = buffer[i];
        }

        delete[] buffer;
        buffer = newBuffer;
    }

    return buffer;
}

char *getline() {
    size_t capacity = 1;
    size_t size = 0;
    char *buffer = alloc_and_copy(NULL, 0, 1);
    char ch = '\n';

    while (std::cin.get(ch)) {
        if (ch == '\n') {
            break;
        }

        if (++size > capacity) {
            buffer = alloc_and_copy(buffer, capacity, capacity * 2);
            capacity *= 2;
        }

        buffer[size - 1] = ch;
    }

    buffer = alloc_and_copy(buffer, capacity, size + 1);
    buffer[size] = '\0';

    return buffer;
}

int main() {
    char *line = getline();
    std::cout << line;
    delete[] line;

    return 0;
}
