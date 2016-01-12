#include <iostream>

class StringPointer {
private:
    std::string *ptr;
    bool owned;
public:
    std::string *operator->() {
        return ptr;
    }

    operator std::string *() {
        return ptr;
    }

    StringPointer(std::string *Pointer) : owned(false), ptr(Pointer) {
        if (ptr == nullptr) {
            ptr = new std::string("");
            owned = true;
        }
    }

    ~StringPointer() {
        if (owned) {
            delete ptr;
        }
    }
};

int main() {
    std::string s1 = "Hello, world!";

    StringPointer sp1(&s1);
    StringPointer sp2(NULL);

    std::cout << sp1->length() << std::endl;
    std::cout << *sp1 << std::endl;
    std::cout << sp2->length() << std::endl;
    std::cout << *sp2 << std::endl;

    return 0;
}
