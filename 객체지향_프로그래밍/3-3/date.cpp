#include<iostream>
using namespace std;

#include "date.h"

int main() {
    Date birth(2014, 3, 20);
    Date independenceDay("1945/8/15");

    cout << birth.getYear() << "," << birth.getMonth() << "," << birth.getDay() << endl;
    independenceDay.show();
}