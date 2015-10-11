#include <iostream>

struct Cls {
    Cls(char c, double d, int i);
private:
    char c;
    double d;
    int i;
};

struct ClsPublic {
    char c;
    double d;
    int i;
};

// Эта функция должна предоставить доступ к полю c объекта cls.
// Обратите внимание, что возвращается ссылка на char, т. е.
// доступ предоставляется на чтение и запись.
char &get_c(Cls &cls) {
    return ((ClsPublic*) &cls)->c;
}

// Эта функция должна предоставить доступ к полю d объекта cls.
// Обратите внимание, что возвращается ссылка на double, т. е.
// доступ предоставляется на чтение и запись.
double &get_d(Cls &cls) {
    return ((ClsPublic*) &cls)->d;
}

// Эта функция должна предоставить доступ к полю i объекта cls.
// Обратите внимание, что возвращается ссылка на int, т. е.
// доступ предоставляется на чтение и запись.
int &get_i(Cls &cls) {
    return ((ClsPublic*) &cls)->i;
}


int main() {
    Cls *u = new Cls('a', 4.3, 876);
    std::cout << get_c(*u) << " " << get_d(*u) << " " << get_i(*u) << std::endl;
    return 0;
}

Cls::Cls(char c, double d, int i) {
    this->c = c;
    this->d = d;
    this->i = i;
}
