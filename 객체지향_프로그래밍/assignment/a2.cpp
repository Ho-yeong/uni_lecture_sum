#include <iostream>
using namespace std;

class Shape {
protected:
    virtual void draw()=0;
};

class Point: public Shape {
public:
    void draw() {
        cout << "This is Point" << endl;
    };
};

class Line: public Shape {
public:
    void draw() {
        cout << "This is Line" << endl;
    };
};

class Circle: public Shape {
public:
    void draw() {
        cout << "This is Circle" << endl;
    };
};

class Triangle: public Shape {
public:
    void draw() {
        cout << "This is Triangle" << endl;
    };
};

class Rectangle: public Shape {
public:
    void draw() {
        cout << "This is Rectangle" << endl;
    };
};

int main() {
    Point p;
    Line l;
    Circle c;
    Triangle t;
    Rectangle r;

    p.draw();
    l.draw();
    c.draw();
    t.draw();
    r.draw();
}