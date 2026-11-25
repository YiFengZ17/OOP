#include <iostream>
#include <cstring>
using namespace std;

struct Person{
    string name;
    Person(const char* s):name(s){ 
        cout << "Person(const char* s)" << endl; 
        }
    Person(const Person& other){ 
        name = other.name;
        cout << "Person(const Person& other)" << endl; 
        }
    ~Person() {}
};

Person copy_func( Person p ) {  
    cout << "in copy_func()" <<endl; 
    return p; 
} // copy ctor called! 

Person nocopy_func(const char *who ) { 
    cout << "in nocopy_func()" <<endl; 
    return Person( who ); 
}  // no copy needed!

int main(){
    Person p1 = copy_func("Tom");
    cout<<"------------------------"<<endl;
    Person p2 = nocopy_func("Oliver");
}