// factorial.cpp
#include <iostream>
#include <thread>
#include "factorial.h"

using namespace std;

Factorial::Factorial() {
    result = 0;
}

void Factorial::setNumber(int n) {
    this->result = n;
}

int Factorial::getNumber() {
    return this->result;
}

void Factorial::calculate(int res, std::promise<int>& p) {
    int ans = 1;
    for (int i = res; i > 0; i--) {
        ans *= i;
    }
    cout << "reached" << endl;
    p.set_value(ans);
    cout << "set the value" << endl;
}
