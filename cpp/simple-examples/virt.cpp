#include <iostream>

struct A {
    void other() const {
        std::cout << "A::other" << std::endl;
    }

    virtual void some() const {
        std::cout << "A::some" << std::endl;
        other();
    }
};

struct B : A {
    virtual void some() const {
        std::cout << "B::some" << std::endl;
    }
};

int main() {
    A a;
    a.some();

    B b;
    b.some();

    return 0;
}
