#include <iostream>
using namespace std;

bool bigger(int a, int b, int& big) {
    if (a == b) 
        return true;
    
    if (a > b) big = a;
    else big = b;

    return false;
}

int main() {
    int a, b, big;
    
    cin >> a;
    cin >> b;

    bool result = bigger(a, b, big);

    cout << "result: " << result << endl;
    cout << "big: " << big << endl;
}