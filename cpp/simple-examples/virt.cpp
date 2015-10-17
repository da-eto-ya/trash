#include <iostream>

struct A {
    virtual void some() const {
        std::cout << "a" << std::endl;
    }
};

struct B : A {
    virtual void some() const {
        std::cout << "b" << std::endl;
    }
};

int main() {
    A a;
    a.some();

    B b;
    b.some();

    return 0;
}
