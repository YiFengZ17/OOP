//: C12:ExplicitKeyword.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Using the "explicit" keyword
#include <iostream>
using namespace std;

class One {
public:
  One() {}
};

class Two {
public:
  explicit Two(const One&) { cout << "inside Two(One)" << endl;}
};

void f(Two) {}

int main() {
  One one;
  //f(one); // No auto conversion allowed
  f(Two(one)); // OK -- user performs conversion
} ///:~
