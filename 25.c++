#include <iostream>
#include <string>
using namespace std;

int letterDistance(char a, char b) {
    return (a > b) ? a - b : b - a;
    //if (a > b) return a - b;
    //else return b - a;
}

string password(string s) {
    string result = "";
    for (int i = 0; i < s.size() - 1; i++) {
        result += to_string(letterDistance(s[i], s[i + 1]));
        //to_string is a function that converts a number to a string
    }
    return result;
}

int main() {
    string s;
    getline(cin, s);
    cout << password(s) << endl;
    return 0;
}

