#include <iostream>

extern int g_global; // Correct: referencing the global variable defined in file1.cpp

void func();

void myfunc() {
    g_global += 2;  // Correct: operating on the global variable

    // s_local is not visible in this file, the following line will cause a compilation error
    //s_local *= g_global;

    func(); // Correct: calling the function defined in file1.cpp
    //hidden();
}
