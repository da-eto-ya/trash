#include <iostream>

class Hi {
public:
    Hi() {
        std::cout << "Hi constructed" << std::endl;
    }

    ~Hi() {
        std::cout << "Hi destructed" << std::endl;
    }
};

int main() {
    Hi *my = new Hi();

    return 0;
}
