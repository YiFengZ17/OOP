#include<iostream>
using namespace std;
// try -fno-elide-constructors, more copy ctor is used.

static int objectCount = 0;
void print(const string& msg){
    cout << msg << ": ";
    cout << "objectCount = " <<objectCount <<endl; 
}

class HowMany {
    public:
        HowMany(){
            objectCount++;
            print("HowMany()");
        }

        HowMany(const HowMany& s){
            objectCount++;
            print("copyHowMany()");
        }

        ~HowMany(){
            objectCount--;
            print("~HowMany()");

        }

};

// Pass and return BY VALUE
HowMany f(HowMany x){
    print("x argument inside f()");
    return x;
}

int main(){

    HowMany h;
    print("after construction of h");

    //HowMany h2;
    //h2 = h;
    //HowMany h3(h);

    HowMany h2 = f(h);
    print("after call to f()");
}