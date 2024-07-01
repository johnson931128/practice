#include <iostream>
#include <math.h>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    int d = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
    int e = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    int D = b * b - 4 * a * c;
    if (D > 0)
        cout << "Two different roots x1=" << d << " , x2=" << e;
    else if (D == 0)
        cout << "Two same roots x=" << d;
    else
        cout << "No real root";
    return 0;
}