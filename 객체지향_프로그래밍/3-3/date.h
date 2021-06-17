#include<iostream>
#include<string>
using namespace std;

class Date {
    int year, month, day;

public:
    Date(int a, int b, int c);
    Date(string a);
    void show();
    int getYear();
    int getMonth();
    int getDay();
};

Date:: Date(int a, int b, int c) {
    year = a; month = b; day = c;
};

int Date:: getYear() {
    return year;
};

int Date:: getMonth() {
    return month;
};

int Date:: getDay() {
    return day;
};

Date:: Date(string s) {
    int index = s.find('/');
    string y = s.substr(0, index);

    int index2 = s.find('/', index + 1);
    string m = s.substr(index + 1, index2 - index - 1);

    int index3 = s.find('/', index2 + 1);
    string d = s.substr(index2 + 1, index3 - index2);
    
    year = stoi(y);
    month = stoi(m);
    day = stoi(d);
};

void Date:: show() {
  cout << year << "년 " << month << "월 " << day << "" << endl;  
};