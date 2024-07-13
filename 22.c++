#include <iostream>
#include <unordered_map>
using namespace std;

// 身份證字母對應的數字
unordered_map<char, int> letterMap = {
    {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}, {'G', 16}, {'H', 17}, {'I', 34}, {'J', 18}, {'K', 19}, {'L', 20}, {'M', 21}, {'N', 22}, {'O', 35}, {'P', 23}, {'Q', 24}, {'R', 25}, {'S', 26}, {'T', 27}, {'U', 28}, {'V', 29}, {'W', 32}, {'X', 30}, {'Y', 31}, {'Z', 33}
};

// 計算檢查碼
int calculateCheckDigit(const string& id) {
    int sum = 0;
    // 加上字母對應的數字
    sum += letterMap[id[0]] / 10 + (letterMap[id[0]] % 10) * 9;
    // 加上後面的數字
    for (int i = 1; i < 9; ++i) {
        sum += (id[i] - '0') * (9 - i);
    }
    sum += id[8] - '0'; // 加上最後一位數
    return (10 - (sum % 10)) % 10; // 計算檢查碼
}

int main() {
    string id;
    cin >> id; // 讀取後 9 碼
    id = ' ' + id; // 在前面加一個空格，方便後續處理

    for (auto& pair : letterMap) {
        id[0] = pair.first; // 嘗試每一個字母
        if (calculateCheckDigit(id) == (id[9] - '0')) { // 如果檢查碼匹配
            cout << pair.first; // 輸出該字母
        }
    }
    cout << endl;

    return 0;
}
