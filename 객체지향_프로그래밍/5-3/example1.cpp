#include <iostream>
using namespace std;

class Circle {
    int radius;
public:
    Circle() {radius = 1;};
    Circle(int radius) {this->radius = radius;};
    int getArea() { return 3.14 * radius *radius; };
};

void swap(Circle& a, Circle& b) {
    Circle tmp;
    tmp = a;
    a = b;
    b = tmp;
};

int main() {
    Circle a;
    Circle b(30);

    cout << "a: " << a.getArea() << endl;
    cout << "b: " << b.getArea() << endl;

    swap(a, b);

    cout << "a: " << a.getArea() << endl;
    cout << "b: " << b.getArea() << endl;
};