#include <iostream>
#include <string>
using namespace std;

// 函數：將十進位整數轉換為二進位字符串
string binary(int n) {
    string result;
    while (n > 0) {
        result = to_string(n % 2) + result; // 將餘數加到結果字符串的前面
        //to_string() 函數用於將整數轉換為字符串
        n /= 2; // n 更新為 n 除以 2 的商
    }
    return result.empty() ? "0" : result; // 如果結果為空，返回 "0" 如果不為空，返回結果
}

int main() {
    int n;
    // 讀取輸入直到 EOF
    while (cin >> n) {
        cout << binary(n) << endl; // 輸出每個整數的二進位表示
    }
    return 0;
}