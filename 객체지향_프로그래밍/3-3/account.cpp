#include<iostream>
using namespace std;

class Account {
    string name;
    int account, balance;

public:
    Account(string n, int a, int b) {
        name = n;
        account = a;
        balance = b;
    };

    void deposit(int m) {
        balance += m;
    };

    string getOwner() {
        return name;
    };

    int inquiry() {
        return balance;
    };

    string withdraw(int r) {
        if (balance < r) {
            return "잔액 부족";
        } else {
            balance -= r;
            return to_string(balance);
        }
    };
};



int main() {
    Account a("simon", 1, 5000);
    a.deposit(50000);

    cout << a.getOwner() << "의 잔액은 " << a.inquiry() << endl;

    string money = a.withdraw(100000);
    cout << a.getOwner() << "의 잔액은 " << money << endl;
};