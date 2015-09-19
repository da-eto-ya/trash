class SomeParent {
private:
    unsigned int width;
    unsigned int height;
public:
    SomeParent(unsigned int width = 0, unsigned int height = 0) : width(width), height(height) { }

    unsigned int getWidth() {
        return width;
    }

    inline unsigned int getHeight();

    unsigned int getArea();
};

unsigned int SomeParent::getHeight() {
    return height;
}

unsigned int SomeParent::getArea() {
    return width * height;
}


int main() {
    SomeParent *p = new SomeParent(3, 2);
    unsigned int w = p->getWidth();
    unsigned int h = p->getHeight();
    unsigned int a = p->getArea();
    delete p;

    return 0;
}
