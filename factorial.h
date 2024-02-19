// factorial.h
#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <future>

class Factorial {
public:
    Factorial();
    void setNumber(int);
    void calculate(int, std::promise<int>&p);
    int getNumber();

private:
    int result;
};

#endif
