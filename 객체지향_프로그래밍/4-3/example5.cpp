#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main() {
    string text;

    cout << "아래에 한 줄을 입력하세여 (exit는 종료) : " << endl;

    while(true) {
        cout << ">>";
        getline(cin, text, '\n');
        if (text == "exit") {
            break;
        };
        if (text == "") {
            continue;
        };
        int size = text.length();

        for (int i = size; i >= 0; i--) {
            cout << text[i];
        };
        cout << endl;

        cout << text << endl;
    };
};