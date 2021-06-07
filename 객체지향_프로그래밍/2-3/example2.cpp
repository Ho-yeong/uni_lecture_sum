#include<iostream>
#include<cstring>
using namespace std;

// 문자열 비교
void stringCompare() {
    char password1[100];
    char password2[100];

    cout << "새 암호를 입력하세요 >>";
    cin >> password1;
    cout << "새 암호를 다시 입력하세요 >>";
    cin >> password2;
    if(strcmp(password1, password2) == 0)
        cout << "같습니다.";
    else
        cout << "같지 않습니다.";
    cout << endl;
}

// x의 개수를 출력
void countX() {
    char c[100];
    int count = 0;
    cout << "문자들을 입력하라(100개 미만)" << endl;
    cin.getline(c, 100);

    int i = 0;
    while(true) {
        if(c[i] == '\n')
            break;
        if(c[i] == 'x')
            count++;
        i++;
    }
    cout << "x 의 개수는" << count << endl;
}

// yes가 입력될때 종료
void exitString() {
    char c[100];

    while(true) {
        cout << "종료하고 싶으면 yes";
        cin.getline(c, 100);
        if(strcmp(c, "yes") == 0) {
            break;
        }
    }
}

int main() {
    exitString();
}