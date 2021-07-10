#include <iostream>
using namespace std;
#include <string>

class Person {
    int id;
    double weight;
    string name;
public:
    void show() {cout << id << "" << weight << "" << name << endl;};
    Person() {id = 1; weight = 20.5; name = "Grace";};
    Person(int id, string name) {this->id = id; this->name = name;};
    Person(int id, string name, double weight) {this->id = id; this->name = name; this->weight = weight;};
};

int main() {
    Person grace, ashley(2, "Ashley"), helen(3, "Helen", 32.5);

    grace.show();
    ashley.show();
    helen.show();
}