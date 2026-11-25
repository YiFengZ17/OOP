#include <iostream>

class MyClass {
public:
    // User-defined conversion from double to MyClass
    MyClass(double value) {
        std::cout << "MyClass constructed from a double: " << value << std::endl;
        m_value = value;
    }
    
    operator int() const {
     std::cout << "MyClass int () " << std::endl;
     return static_cast<int>(m_value);
   }

private:
   double m_value;

};

void func(int i) {
    std::cout << "func(int): " << i << std::endl;
}

void func(double d) {
    std::cout << "func(double): " << d << std::endl;
}

void func(MyClass mc) {
    std::cout << "func(MyClass)" << std::endl;
}

int main() {
    int i = 5;
    double d = 5.5;
    MyClass mc(10.0);

    func(i);
    std::cout<< " ----0----- " << std::endl;
    func(d);
    std::cout<< " ----1----- " << std::endl;
    func(mc);
    std::cout<< " ----2----- " << std::endl;
    func(10.0);
    std::cout<< " ----3----- " << std::endl;
    func(static_cast<MyClass>(10.0)); // This will work because we're explicitly casting

    func('a'); 

    return 0;
}
