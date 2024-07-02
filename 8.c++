#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
    int num;
    cin >> num;
    bool firstFactor = true; // 用於檢查是否為第一個因數，以決定是否輸出'*'
    for (int i = 2; i <= sqrt(num); i++) {
        int count = 0; // 計算質因數i的次數
        while (num % i == 0) {
            num /= i; // 將num除以i
            count++;
        }
        if (count > 0) {
            if (!firstFactor) { // 如果不是第一個因數，則輸出'*'
                cout << " * ";
            }
            cout << i;
            if (count > 1) {
                cout << "^" << count;
            }
            firstFactor = false;
        }
    }
    if (num > 1) {
        if (!firstFactor) {
            cout << " * ";
        }
        cout << num;
    }
    return 0;
}