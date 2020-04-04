//
//@brief: Main function based on BigInt class to do math operations on bigint.
//@copyright: Copyright NPU-Franklin 2020
//@license: MIT License
//@birth: created by NPU-Franklin 2020-3-31
//@version: 4.0.2
//@revision: last revised by NPU-Franklin 2020-4-4
//

#include <iostream>
#include <thread>
#include <mutex>
#include "BigInt.h"

using namespace std;

mutex mu;

int main() {
    BigInt a, b;
    cin >> a >> b;

    thread thread0([&a, &b] {
        mu.lock();
        cout << a + b << endl;
        mu.unlock();
    });
    thread thread1([&a, &b] {
        mu.lock();
        cout << a - b << endl;
        mu.unlock();
    });
    thread thread2([&a, &b] {
        mu.lock();
        cout << a * b << endl;
        mu.unlock();
    });
    thread thread3([&a, &b] {
        mu.lock();
        cout << a / b << endl;
        mu.unlock();
    });
    thread thread4([&a, &b] {
        mu.lock();
        cout << a % b << endl;
        mu.unlock();
    });

    thread0.join();
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    return 0;
}