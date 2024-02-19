// main.cpp
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include "factorial.h"

using namespace std;

class FactorialSummation {
private:
    int totalObjects, result;
    Factorial* fac;
    vector<thread> threads;
    vector<promise<int>> p;
    vector<future<int>> f;
    std::mutex resultMutex;

    void calculate() {
        cout << "total Objects: " << totalObjects << endl;
        for (int i = 0; i < totalObjects; i++) {
            cout << "i: " << i << endl;
            int n = fac[i].getNumber();
            cout << "n: " << n << endl;
            threads.emplace_back(&Factorial::calculate, std::ref(fac[i]), n, std::ref(p[i]));
        }
        cout << "Launched all the threads from main." << endl;
    }

    void getResult() {
        for (int i = 0; i < totalObjects; i++) {
            f.push_back(p[i].get_future());
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
        totalObjects = n;
    }

    void makeObjects() {
        cout << "total Objects:  " << totalObjects << endl;
        fac = new Factorial[totalObjects];
        for (int i = 0; i < totalObjects; i++) {
            cout << "i: " << i << endl;
            fac[i].setNumber(totalObjects - i);
        }
    }

    int calculateResult() {
        calculate();
        joinThreads();
        getResult();
        for (int i = 0; i < totalObjects; i++) {
            std::lock_guard<std::mutex> lock(resultMutex);
            result += f[i].get();
        }
        return result;
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
