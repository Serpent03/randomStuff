// factorial.cpp
#include <iostream>
#include <thread>
#include "factorial.h"

using namespace std;

Factorial::Factorial() {
    result = 0;
}

void Factorial::setNumber(int n) {
    result = n;
}

int Factorial::getNumber() {
    return result;
}

void Factorial::calculate(int res, std::promise<int>& p) {
    int ans = 1;
    for (int i = res - 1; i > 0; i--) {
        ans *= i;
    }
    cout << "reached" << endl;
    p.set_value(ans);
    cout << "set the value" << endl;
}
