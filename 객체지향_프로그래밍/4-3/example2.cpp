#include <iostream>
#include <string>
using namespace std;

int main() {
    string text;

    cout << "문자열 입력: ";
    getline(cin, text);

    int count = 0, index = 0;
    while(1) {
        index = text.find('a', index);
        if (index == -1) {
            break;
        }
        count++;
        index++;
    }
    cout << "문자 a는" << count << "개가 있습니다." << endl;
}