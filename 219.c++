#include <iostream>
using namespace std;


int main() {
    int num1 = 5;
    int num2 = 10;
    cout << "Enter two numbers:";
    cin >> num1 >> num2;
    cout << "Sum is " << num1 + num2 << endl;
    if (num1 == num2)
        cout << num1 << "==" << num2 << endl;
    cout << "num1 is " << num1 << endl;    
    return 0;
}