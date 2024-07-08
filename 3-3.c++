#include <iostream>
using namespace std;
class GradeBook
{
    public:
    void displayMessage(string coursename)
    {
        cout << "Welcome to the Grade Book for\n" << coursename << "!" << endl;
    }
};
int main() {
    string nameOfCourse;
    GradeBook myGradeBook; //remeber to create an object of the class
    cout << "Please enter the course name:" << endl;
    getline(cin, nameOfCourse);
    myGradeBook.displayMessage(nameOfCourse);
    return 0;
}