#include <iostream>
#include <string>
#include <map> // 使用 map 函式庫來建立羅馬數字與整數的對應關係
using namespace std;

// 將羅馬數字轉換為整數
int romanToInt(string s) {
    map<char, int> roman{{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    // roman是一個map(映射)，將羅馬數字與整數對應起來
    int total = 0;
    for (int i = 0; i < s.length(); i++) {
        if (i + 1 < s.length() && roman[s[i]] < roman[s[i + 1]]) {
            total += roman[s[i + 1]] - roman[s[i]];
            i++; // 跳過下一個字符
        } else {
            total += roman[s[i]];
        }
    }
    return total;
}

// 將整數轉換為羅馬數字
string intToRoman(int num) {
    string romanNumerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string result = "";
    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            num -= values[i];
            result += romanNumerals[i];
        }
    }
    return result;
}

int main() {
    string a, b;
    while (cin >> a >> b) {
        if (a == "#" && b == "#") break;
        int aInt = romanToInt(a);
        int bInt = romanToInt(b);
        int diff = abs(aInt - bInt);
        if (diff == 0) {
            cout << "ZERO" << endl;
        } else {
            cout << intToRoman(diff) << endl;
        }
    }
    return 0;
}