#include <iostream>

class A {
public:
    A() : a(1) {
        std::cout << "A created (a: " << a << ")" << std::endl;
    }

    virtual ~A() {
        std::cout << "A desctucted" << std::endl;
    }

private:
    int a;
};

class B : public A {
public:
    B() : b(2) {
        std::cout << "B created (b: " << b << ")" << std::endl;
    }

    virtual ~B() {
        std::cout << "B desctucted" << std::endl;
    }

private:
    int b;
};

int main() {
    B *b = new B();
    delete b;

    return 0;
}