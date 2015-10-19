#include <iostream>

struct A {
    virtual void some() const {
        std::cout << "A::some" << std::endl;
        other();
    }

private:
    virtual void other() const {
        std::cout << "A::other" << std::endl;
    }
};

struct B : private A {
    virtual void some() const {
        std::cout << "B::some" << std::endl;
    }

    void opa() {
        std::cout << "B::opa" << std::endl;
        some();
    }

    virtual void other() const {
        std::cout << "B::other" << std::endl;
    }
};

int main() {
    A a;
    a.some();

    B b;
    b.some();
    b.opa();

    B &bb = b;
    bb.some();

    bb.other();

    return 0;
}
