#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

ostream& fixed_width(ostream& os) {
    return os << setw(15) << setfill(' ');
}

int main () {
    // int age = 18;

    // double pi = 3.14159265358979323846;
    
    // cout.precision(10);
    // cout << setw(15) << age << endl << setw(15) << pi << endl << setw(15) << age << endl;
    
    // cout << fixed_width << age 
    //      << fixed_width << pi 
    //      << fixed_width << age << endl;

    string str = "Hello, Hangzhou! Today is windy";
    cout << str << endl;

    // string str2("I am Jone."); 

    // string str3 = str + str2; 

    // cout << str3 << endl;
    string sub_str = "Hangzhou";

    //cout << str.find(sub_str);

    string rep_str = "Beijing";

    int pos = str.find(sub_str);

    cout<< str.replace(pos, rep_str.length(), rep_str) << endl;

    ofstream ofstr("text.txt");
    ofstr << str << endl;
    cout << str << endl;

    ifstream ifstr("text.txt");
    string input_str;
    ifstr >> input_str;

    cout << input_str << endl;

}