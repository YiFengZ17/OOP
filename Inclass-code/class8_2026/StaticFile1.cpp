#include <iostream>

// Global variable, accessible in other files through the extern keyword
int g_global;

// Static global variable, only visible within this file
static int s_local = 42;

// Non-static function, accessible in other files
void func() {
    static int ss_times = 0;
    ss_times++;
    std::cout << "func() called. g_global: " << g_global << " ss_times: " << ss_times << std::endl;
}

// Static function, only visible within this file
static void hidden() {
    std::cout << "hidden() called. s_local: " << s_local << std::endl;
}