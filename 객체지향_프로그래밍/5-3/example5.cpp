#include <iostream>
using namespace std;


char& find(char a[], char c, bool& success) {
     int i = 0;
     while(a[i]) {
         if (a[i] == c) {
             success = true;
             return a[i];
         };
         i++;
     };
     return a[0];
};

int main() {
    char s[] = "Sike";
    bool b = false;

    char& loc = find(s, 'M', b);
    if (b == false) {
        cout << "없음" << endl;
        return 0;
    }
    loc = 'm';
    cout << s << endl;
};