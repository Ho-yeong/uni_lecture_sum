#include<iostream>
using namespace std;

#include"random.h"

int main() {
    Random r;
    cout << "-- 0에서" << RAND_MAX << "까지의 랜덤 정수 10개--" << endl;
    for(int i=0; i < 10; i++) {
        int n = r.next();
        cout << n << " ";
    };

    int start = 2;
    int end = 10;

    cout << endl << endl << start << "에서 부터 " << end << "까지의 랜덤정수 10개 --" << endl;
    for (int i=0; i<10; i++) {
        int n = r.nextInRange(start, end);
        cout << n << " ";
    };
    cout << endl;
}