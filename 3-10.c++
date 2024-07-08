#include <iostream>
#include "Gradebook.h"
using namespace std;

int main()
{
    string nameOfCourse1, nameOfCourse2;
    getline(cin , nameOfCourse1);
    getline(cin , nameOfCourse2);
    Gradebook gradebook1(nameOfCourse1);
    Gradebook gradebook2(nameOfCourse2);
    cout << "gradebook1 created for course : " << gradebook1.getCourseName() << endl;
    cout << "gradebook2 created for course : " << gradebook2.getCourseName() << endl;
}