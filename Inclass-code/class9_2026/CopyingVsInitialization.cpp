//: C12:CopyingVsInitialization.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 2000
// Copyright notice in Copyright.txt

#include <iostream>
using namespace std;

class Fi {
public:
	Fi() {}
};

class Fee {
public:
	Fee(int) { cout << "Fee(int)" << endl; }
	Fee(const Fi&) { cout << "Fee(const Fi&)" << endl; }
	Fee(const Fee&) { cout << "Fee(const Fee&)" << endl; }
	Fee& operator=(const Fee&) { cout << "Fee=" << endl; return *this; }
};

int main() {
	Fee fee = 1; // Fee(int)
	Fee fum = fee; //Fee(Fee)
	Fi fi;
	fum = fi; //Fee(Fi) and  =
} ///:~
