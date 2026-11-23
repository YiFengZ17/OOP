#include <iostream>
using namespace std;


struct Student{
    int id;
    char address[10000]; 
};

void foo1(Student s1)
{
    cout << s1.id <<endl;
    s1.id ++;
}

void foo2(Student *s2)
{
    cout << s2->id <<endl;
    s2->id++;
}

void foo3(Student &s3)
{
    cout << s3.id <<endl;
    s3.id++;
}

int main()
{
	Student s;
    s.id = 0;

    foo1(s);
    cout << s.id << endl;
    foo2(&s);
    cout << s.id << endl;
    foo3(s);
    cout << s.id << endl;

	return 0;
}