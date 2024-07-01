#include <iostream>
#include <string>
using namespace std;

string decrypt(const string& cipherText, int K) {
    string plainText = "";
    for (char c : cipherText) {
        // 將字元轉換為ASCII碼並減去K的值
        char decryptedChar = c + K;
        // 將得到的ASCII碼轉換回字元並加到明碼字串中
        plainText += decryptedChar;
    }
    return plainText;
}

int main() {
    string cipherText;
    getline(cin, cipherText);
    int K = -7;
    cout << decrypt(cipherText, K) << endl;
    return 0;
}