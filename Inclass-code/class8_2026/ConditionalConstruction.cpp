#include <iostream>
using namespace std;

class X {
public:
    X(int i, int j) {
        std::cout << "X constructed with value " << i << ", " << j << std::endl;
        m_i = i;
        m_j = j;
    }
    ~X() {
        std::cout << "X destroyed " << m_i << ", " << m_j << std::endl;
    }
    int m_i, m_j;
};

void f(int x) {
    if (x > 10) {
        static X my_X(x, x * 21); // X only constructed when x > 10
        // ... do something with my_X ...
    }
    if (x>15)
    {
        static X my_X2(x, x); 
    }
    // my_X is not destroyed when f exits, because it is static
}

int main() {
    f(5);  // my_X is not constructed here, because x <= 10
    cout << "After f(5)" << endl;
    f(15); // my_X is constructed here, because x > 10
    cout << "After f(15)" <<endl;
    f(20);   
    cout << "After f(20)" <<endl;
    f(30);   
    cout << "After f(30)" <<endl;
    return 0;
}
