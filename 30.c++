#include <bits/stdc++.h>
using namespace std;

int a[10005];  // 全域陣列，最大長度為 10005

int main() {
    int n;
    while (cin >> n) {  // 持續讀取輸入的數字 n
        double sum = 0;  // 初始化 sum 為 0，並設定為 double 型態
        for (int i = 0; i < n; i++) {
            cin >> a[i];  // 讀取 n 個數字並存入陣列 a
            sum += a[i];  // 將每個數字累加到 sum
        }
        if ((sum / n) > 59)  // 計算平均值並判斷是否大於 59
            cout << "no\n";  // 如果大於 59，輸出 "no"
        else
            cout << "yes\n";  // 否則輸出 "yes"
    }
}