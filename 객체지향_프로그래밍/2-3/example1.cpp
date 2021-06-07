#include<iostream>
using namespace std;

double biggest(double x[], int n) {
    double r;
    r = x[0];
    for(int i=0; i<n;i++) {
        if(r < x[i])
            r = x[i];
    }
    return r;
}

int main() {

    for(int i=1; i <= 100; i++) {
        cout << i;
        if (i % 10 == 0)
            cout << endl;
        else 
            cout << '\t';
    }

    for(int i =1; i <= 9; i++) {
        for(int j= 1; j <=9; j++) {
            cout << i << "x" << j << "=" << i * j << "\t";
        }
        cout << endl;
    }

    int x, y;
    cin >> x >> y;
    if (x > y)
        cout << x + "\n";
    else
        cout << y + "\n";

    double a[5];
    cout << "5개의 실수를 입력하라>>";
    for (int i=0; i < 5; i++) {
        cin >> a[i];
    }
    cout << "제일 큰 수 = " << biggest(a, 5) << endl;
}