#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
using namespace std;
int main() {
    unordered_map<string, int> wordCount;
    string text = "this is a test this is only a test";

    stringstream ss(text);
    string word;
    while (ss >> word) {
        wordCount[word]++;
    }

    for (const auto &pair : wordCount) {
        cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
