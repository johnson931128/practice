#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <cctype>//cctype最常見的函數是isdigit()，用來判斷一個字符是否是數字字符
using namespace std;

int count(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : throw invalid_argument("Division by zero");
        case '%': return a % b;
        default: throw invalid_argument("Invalid operator");
    }
}

int calculate(string expr) {
    istringstream issexpr(expr);
    stack<int> nums;
    stack<char> opers;
    unordered_map<char, int> prior = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}};
    char c;
    while (issexpr >> c) {
        if (isdigit(c)) {
            issexpr.putback(c);//將c放回issexpr
            int num;
            issexpr >> num;//將c轉換成數字
            nums.push(num);//將數字放入nums
        } else if (c == '(') {
            opers.push(c);
        } else if (c == ')') {
            while (!opers.empty() && opers.top() != '(') {
                int b = nums.top(); nums.pop();
                int a = nums.top(); nums.pop();
                char op = opers.top(); opers.pop();
                nums.push(count(a, b, op));
            }
            opers.pop(); // Remove '('
        } else {
            while (!opers.empty() && prior[opers.top()] >= prior[c]) {
                int b = nums.top(); nums.pop();
                int a = nums.top(); nums.pop();
                char op = opers.top(); opers.pop();
                nums.push(count(a, b, op));
            }
            opers.push(c);
        }
    }
    while (!opers.empty()) {
        int b = nums.top(); nums.pop();
        int a = nums.top(); nums.pop();
        char op = opers.top(); opers.pop();
        nums.push(count(a, b, op));
    }
    return nums.top();
}

int main() {
    string expression;
    cout << "Enter an expression: ";
    getline(cin, expression);
    try {
        cout << "Result: " << calculate(expression) << endl;
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
    return 0;
}