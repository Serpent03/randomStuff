// main.cpp
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include "factorial.h"

using namespace std;

class FactorialSummation {
private:
    int totalObjects;
    int result = 0;
    Factorial* fac;
    vector<thread> threads;
    vector<promise<int>> p;
    vector<future<int>> f;
    std::mutex resultMutex;

    void calculate() {
        cout << "total Objects: " << totalObjects << endl;
        for (int i = 0; i < totalObjects; i++) {
            cout << "i: " << i << endl;
            int n = this->fac[i].getNumber();
            cout << "n: " << n << endl;
            threads.emplace_back(&Factorial::calculate, std::ref(fac[i]), n, std::ref(p[i]));
        }
        cout << "Launched all the threads from main." << endl;
    }

    void getResult() {
        for (int i = 0; i < totalObjects; i++) {
            this->f.push_back(p[i].get_future());
        }
    }

    void joinThreads() {
        for (int i = 0; i < totalObjects; i++) {
            if (threads[i].joinable())
                threads[i].join();
            else
                cout << "Error: Thread " << i << " not joinable." << endl;
        }
    }

public:
    FactorialSummation(int n) {
        this->totalObjects = n;
        this->result = 0;
    }

    void makeObjects() {
        cout << "total Objects:  " << totalObjects << endl;
        this->fac = new Factorial[totalObjects];
        for (int i = 0; i < totalObjects; i++) {
            cout << "i: " << i << endl;
            this->fac[i].setNumber(totalObjects - i);
            this->p.push_back(promise<int>());
        }
    }

    int calculateResult() {
        calculate();
        joinThreads();
        getResult();
        int _result = 0;
        for (int i = 0; i < totalObjects; i++) {
            std::lock_guard<std::mutex> lock(resultMutex);
            this->result += f[i].get();
        }
        return this->result;
    }
    ~FactorialSummation() {
        delete[] fac;
    }
};

int main() {
    int objCnt;
    cout << "Enter number of objects: ";
    cin >> objCnt;
    FactorialSummation fs(objCnt);
    fs.makeObjects();
    cout << "Result: " << fs.calculateResult() << endl;

    return 0;
}
