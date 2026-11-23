#include <iostream>
using namespace std;

class A {
public:
    A() { cout << "Constructor" << endl; }
    A(const A&) { cout << "Copy Constructor" << endl; }
    ~A() { cout << "Destructor" << endl; }
};

A createA() {
    A a;
    return a;   // here invoke RVO // to disable it, using -fno-elide-constructors
}

int main() {
    A obj = createA();
}