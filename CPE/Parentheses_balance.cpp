#include <iostream>
#include <limits> // 確保這一行存在
#include <stack>
#include <string>

int main() {
  int n;
  std::cin >> n;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (n-- > 0) {
    std::string s;
    std::getline(std::cin, s);

    std::stack<char> st;
    bool is_pb = true;

    for (auto c : s) {
      if (c == '(' || c == '[') {
        st.push(c);
      } else if (c == ')') {
        if (st.top() == '(') {
          st.pop();
        } else {
          is_pb = false;
          break;
        }
      } else if (c == ']') {
        if (st.top() == '[') {
          st.pop();
        } else {
          is_pb = false;
          break;
        }
      }
    }
    if (st.empty() && is_pb == true) {
      std::cout << "Yes" << std::endl;
    } else {
      std::cout << "No" << std::endl;
    }
  }
  return 0;
}
