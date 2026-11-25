#include <iostream>
#include <cstring>
using namespace std;

struct Person{
    char * name;
    Person(const char* s){
        name = new char[strlen(s)+1];
        strcpy(name, s);
    }

    Person(const Person& p){
        name = new char[strlen(p.name)+1];
        strcpy(name, p.name);
    }
    
    ~Person() {
        cout << " in Dtor" <<endl;
        delete [] name;
    }
};

int main(){
    Person p1("Tom");
    Person p2(p1);

    cout << (void*)p1.name <<endl;
    cout << (void*)p2.name <<endl;

}