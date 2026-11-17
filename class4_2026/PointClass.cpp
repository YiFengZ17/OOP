// C++ style for Point

#include <iostream>
using namespace std;

int px = 0;
int py = 0;

int pz = 0;


void test_region()
{
    cout << "A global test region" <<endl;
}


class Point {

    private:
        int px, py;

    public:
        void init(int ix, int iy)
        {
            px = ix;
            py = iy;
        }

        void print()
        {
            cout << "point at (" << px << ", " << py << ")" << endl;
        }

        void move(int dx, int dy)
        {
            px += dx;
            py += dy;
        }

        void change(int ix, int iy)
        {
            px = ix;
            py = iy;
        }

        void test_region();
};

void Point::test_region()
{
    px++;
    ::px++;
    pz++;

    cout << "px: " << px << "; global px: " << ::px << "pz: " << pz <<endl;

    ::test_region();
}



int main()
{
    Point p;
    p.init(2, 3);
    p.print();
    p.move(4, 4);
    p.print();
    
    cout << px <<endl;
    px++;
    cout << px << endl;
    test_region();
    
    //p.px = 1;
    //p.py =2;
    //p.print();
    p.change(1, 3);
    p.print();
    p.test_region();


}