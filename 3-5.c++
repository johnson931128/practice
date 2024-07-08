#include <iostream>
#include <string>
using namespace std;
class Gradebook
{
    public:
        void setCourseName(string name)
        {
            courseName = name;
        }

        string getCourseName()
        {
            return courseName;
        }

        void DisplayMessage()
        {
            cout << "Welcome to the grade book for\n" << getCourseName() << "!" << endl;
        }
    private:
        string courseName;  
};

int main()
{
    string nameOfCourse;
    Gradebook myGradebook;
    myGradebook.setCourseName("C++ Programming");
    cout << "The initial gradebook name is :\n" << myGradebook.getCourseName() << "\n" << endl;
    cout << "Please enter the new gradebook name : " << endl;
    cin.ignore();
    getline(cin , nameOfCourse);
    myGradebook.setCourseName(nameOfCourse);
    cout << endl;
    myGradebook.DisplayMessage();
}
