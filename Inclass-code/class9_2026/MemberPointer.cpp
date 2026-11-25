#include <iostream>
using namespace std;

class MyClass {
public:
    int data;
    void display() { cout << data << endl; }
};

int main() {
    MyClass obj;
    obj.data = 42;
       
    // Pointer to member variable
    int MyClass::*ptrToData = &MyClass::data;
    
    // Pointer to member function
    void (MyClass::*ptrToFunc)() = &MyClass::display;
    
    // Using an object instance and pointer to member variable
    cout << obj.*ptrToData << endl; // Outputs 42
    
    // Using an object instance and pointer to member function
    (obj.*ptrToFunc)(); // Calls obj.display() which outputs 42

    return 0;
}
