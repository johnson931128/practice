#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        // 檢查是否為等差數列
        if (b - a == c - b && c - b == d - c) {
            int commonDifference = b - a;
            cout << a << " " << b << " " << c << " " << d << " " << d + commonDifference << endl;
        }
        // 檢查是否為等比數列
        else if (b / a == c / b && c / b == d / c) {
            int commonRatio = b / a;
            cout << a << " " << b << " " << c << " " << d << " " << d * commonRatio << endl;
        }
    }
    return 0;
}