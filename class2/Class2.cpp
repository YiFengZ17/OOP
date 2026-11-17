#include <iostream>
#include <string>
#include <string.h>
using namespace std;

int main ()
{
    // cout << "Hello World!" << endl;
    // int age; 
    // cin >> age;
    // cout << "I am " << age  << "  year old"  << endl;

    string s1; 
    s1  = "Hangzhou";

    string s2; 
    s2 = "Zijingang";

    string s3 = s1 + " " + s2; 

    cout << s3; 

    char cstr1[20] = "abc";
    char cstr2[20];
    strcpy(cstr2, cstr1);
}