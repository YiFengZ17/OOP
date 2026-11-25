//: C12:AutomaticTypeConversion.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt
// Type conversion constructor

#include <iostream>
using namespace std;

class One {
public:
	One() {}
};

class Two {
public:
	Two(const One&) { cout << "inside Two(One)" << endl;}
};

void f(Two) {}

int main() {
	One one;
	f(one); // Wants a Two, has a One
} ///:~
