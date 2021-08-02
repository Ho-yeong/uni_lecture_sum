#include <iostream>
using namespace std;

class Calc {

public:
    int sum(int a, int b) {
        return a + b;
    };

    int sum (int a, int b, int c) {
        return a + b + c;
    }

    double sum(double a, double b) {
        return a + b;
    };
    
    double sum (double a, double b, double c) {
        return a + b + c;
    }
};

int main () {
    Calc c;
    cout << "int + int: " << c.sum(1, 2) << endl;
    cout << "int + int + int: " << c.sum(1, 2, 3) << endl;
    cout << "double + double: " << c.sum(1.1, 1.2) << endl;
    cout << "double + double + double: " << c.sum(1.1, 1.2, 1.3) << endl;
}