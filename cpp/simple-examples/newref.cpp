#include <iostream>

class Hi {
public:
    int value;

    Hi(int value) : value(value) {
        std::cout << "Hi(" << this->value << ") constructed" << std::endl;
    }

    Hi(const Hi &other) : value(other.value) {
        std::cout << "Hi(" << this->value << ") constructed from Hi(" << other.value << ")" << std::endl;
    }

    ~Hi() {
        std::cout << "Hi(" << value << ") destructed" << std::endl;
    }

    Hi &operator=(const Hi &rhs) {
        std::cout << "Hi(" << this->value << ") := Hi(" << rhs.value << ")" << std::endl;

        if (this != &rhs) {
            value = rhs.value;
        }

        return *this;
    }
};

int main() {
    Hi &a0 = *new Hi(0);
    Hi *a1 = new Hi(1);

    return 0;
}
