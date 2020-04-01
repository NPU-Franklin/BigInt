#include <iostream>
#include <thread>
#include "BigInt.h"

using namespace std;

int main() {
    BigInt a, b;
    cin >> a >> b;

    thread thread0([&a, &b]{cout << a + b << endl;});
    thread0.join();

    thread thread1([&a, &b]{cout << a - b << endl;});
    thread1.join();

    thread thread2([&a, &b]{cout << a * b << endl;});
    thread2.join();

    thread thread3([&a, &b]{cout << a / b << endl;});
    thread3.join();

    thread thread4([&a, &b]{cout << a % b << endl;});
    thread4.join();

    return 0;
}