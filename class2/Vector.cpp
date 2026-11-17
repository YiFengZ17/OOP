#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> x;
    for (int a = 0 ; a < 10 ; a++)
    { 
        x.push_back(a);
        cout << a << " " << x.size() << " " << x.capacity() << endl;
    }

    for (int i = 0; i < x.size(); i++)
        cout << x[i] << " ";
    
    cout << endl;

    vector<int>::iterator p;
    for (p = x.begin(); p < x.end(); p = p+5)
        cout << *p << " " ;
    
    cout << endl;
}
