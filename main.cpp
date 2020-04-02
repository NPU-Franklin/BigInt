#include <iostream>
#include <thread>
#include <mutex>
#include "BigInt.h"
//TODO(NPU-Franklin): add comments.
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