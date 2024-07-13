#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main()
{
    string expr = "123 4.67 tennt";
    istringstream issexpr(expr);
    int integer;
    double flaoting;
    string str;
    issexpr >> integer >> flaoting >> str;
    cout << "Integer: " << integer << endl;
    cout << "Floating: " << flaoting << endl;
    cout << "String: " << str << endl;
    return 0;
}