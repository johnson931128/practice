#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

bool isValidTaiwanID(const string& id) {
    if (id.length() != 10) return false; // 檢查長度是否為10

    // 英文字母對應的數字
    std::unordered_map<char, int> letterMap = {
        {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14},
        {'F', 15}, {'G', 16}, {'H', 17}, {'I', 34}, {'J', 18},
        {'K', 19}, {'L', 20}, {'M', 21}, {'N', 22}, {'O', 35},
        {'P', 23}, {'Q', 24}, {'R', 25}, {'S', 26}, {'T', 27},
        {'U', 28}, {'V', 29}, {'W', 32}, {'X', 30}, {'Y', 31},
        {'Z', 33}
    };

    // 檢查首字母是否有效
    if (letterMap.find(id[0]) == letterMap.end()) return false;

    // 計算第一個字母代表的數字的分數
    int score = (letterMap[id[0]] % 10) * 9 + letterMap[id[0]] / 10;

    // 從右到左依次乘1到8，加上最後一碼
    for (int i = 1; i < 9; ++i) {
        if (!isdigit(id[i])) return false; // 檢查是否為數字
        score += (id[i] - '0') * (9 - i);
    }

    if (!isdigit(id[9])) return false; // 檢查最後一碼是否為數字
    score += id[9] - '0';

    // 檢查是否整除於10
    return score % 10 == 0;
}

int main() {
    string id;
    cout << "Enter Taiwan ID: ";
    cin >> id;

    if (isValidTaiwanID(id)) {
        cout << id << "\nreal" << endl;
    } else {
        cout << id << "\nfake" << endl;
    }
    return 0;
}