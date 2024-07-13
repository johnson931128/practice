#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

int calculateArmstrong(int n) {
    string num = to_string(n);
    int sum = 0;
    int power = num.length();//計算位數
    
    for (char c : num) {
        int digit = c - '0';//ACSII碼轉換為數字
        sum += pow(digit, power);
    }
    
    return sum;
}

vector<int> findArmstrongNumbers(int n, int m) {
    vector<int> armstrongNumbers;
    
    for (int i = n; i <= m; i++) {
        if (calculateArmstrong(i) == i) {
            armstrongNumbers.push_back(i);
            //將找到的阿姆斯壯數加入到vector中
        }
    }
    return armstrongNumbers;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> armstrongNumbers = findArmstrongNumbers(n, m);
    if (armstrongNumbers.empty()) {
        cout << "none";
    } else {
        for (int num : armstrongNumbers){
            //輸出vector中的每個元素
            cout << num << " ";
        }
    }
    return 0;
}  
