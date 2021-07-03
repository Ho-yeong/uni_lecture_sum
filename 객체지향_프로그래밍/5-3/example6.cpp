#include <iostream>
using namespace std;

class MyIntStack {
    int p[10];
    int top;
public:
    MyIntStack() { top = 0; };
    ~MyIntStack();
    bool push(int n);
    bool pop();
    void show();
};

bool MyIntStack::push(int n) {
    if (top+ 1 > 10) {
        return false;
    }
    p[top] = n;
    top++;
    return true;
};

bool MyIntStack::pop() {
    if (top - 1 < 0) {
        return false;
    };

    p[top] = 0;
    top--;
    return true;
};

void MyIntStack::show() {
    for (int i = 0; i < top; i++ ) {
        cout << p[i] << endl;
    };
};

int main() {
    MyIntStack s;
    s.show();
    s.push(1);
    s.push(2);
    s.push(3);
    s.show();
    s.pop();
    s.pop();
    s.show();
};