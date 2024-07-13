#include <iostream>
using namespace std;

// 函數用於計算最大公因數
int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;//取餘數
        a = t;
    }
    return a;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl; // 輸出最大公因數
    return 0;
}