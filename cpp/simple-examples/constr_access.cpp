#include <iostream>

struct Foo {
    void say() const { std::cout << "Foo says: " << msg << "\n"; }

protected:
    Foo(const char *msg) : msg(msg) { }

private:
    const char *msg;
};

void foo_says(const Foo &foo) { foo.say(); }

struct Boo : Foo {
    Boo(const char *msg) : Foo(msg) { }
    virtual ~Boo() { }
};

const Foo get_foo(const char *msg) {
    Boo *boo = new Boo(msg);
    return *boo;
}

int main() {
    char msg[] = "hello";
    foo_says(get_foo(msg));
    return 0;
}
