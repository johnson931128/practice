#include <iostream>
#include <string>
using namespace std;

string inverse(string s){
    string a;
    bool leadingZero = true;
    for(int i = s.length()-1; i >= 0; i--){
        if (s[i] != '0' || !leadingZero){
            // 如果不是前導零或者已經有數字了，就加入
            a += s[i];
            leadingZero = false;
        }
    }
    if (a.empty()){
        // 如果結果為空，返回 "0"
        return "0";
    }
    return a;
}

int main(){
    string s;
    while(getline(cin,s)){
        cout << inverse(s) << endl;
    }
    return 0;
}