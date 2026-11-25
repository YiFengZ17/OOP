#include <iostream>

class MyClass {
public:
    void show() {
        std::cout << "MyClass::show() called" << std::endl;
    }
};

class Invoker {
    MyClass* object;
public:
    Invoker(MyClass* obj) : object(obj) {}

    // overload ->* 
    auto operator->*(void (MyClass::*func)()) {
        return [this, func] { return (object->*func)(); };
    }
};

int main() {
    MyClass obj;
    Invoker invoker(&obj);

    void (MyClass::*func)() = &MyClass::show; 
    (obj.*func)(); // direct call
    (invoker->*func)();

    return 0;
}
