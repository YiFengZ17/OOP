#include <iostream>

class A {
    public:
        virtual int test() { }
};

class B: public A {
    public: 
        virtual int test() { }
};

class C {
    public: virtual int test() { }
};

int main(){
    A *pA1 = new B();
    B *pB = dynamic_cast<B*>(pA1);  //safe downcast
    C *pC = dynamic_cast<C*>(pA1);  //not safe, will return a NULL pointer
}

