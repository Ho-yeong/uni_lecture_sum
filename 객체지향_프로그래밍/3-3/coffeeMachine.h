#ifndef COFFEEMACHINE_H
#define COFFEEMACHINE_H

#include<iostream>
using namespace std;


class CoffeeMachine {
    int coffee, water, sugar;

public:
    CoffeeMachine(int c, int w, int s) {
        coffee = c;
        water = w;
        sugar = s;
    };

    void drinkEspresso() {
        if (coffee < 1 || water < 1) {
            return;
        }
        coffee -= 1;
        water -= 1;
    };

    void drinkAmericano() {
        if (coffee < 1 || water < 2) {
            return;
        }
        coffee -= 1;
        water -= 2;
    };

    void drinkSugarCoffee() {
        if (coffee < 1 || water < 1 || sugar < 1) {
            return;
        }
        coffee -= 1;
        water -= 1;
        sugar -= 1;
    };

    void show() {
        cout << "커피: " << coffee << " 물: " << water << " 설탕: " << sugar << endl;
    };

    void fill() {
        coffee = 10;
        water = 10;
        sugar = 10;
    };
};

#endif