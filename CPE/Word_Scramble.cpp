#include <algorithm> // 用於 reverse
#include <cctype>    // 用於 isspace
#include <iostream>  // 用於 cin, cout
#include <string>    // 用於 string

int main() {
  std::string line;

  while (std::getline(std::cin, line)) {
    size_t start = 0;
    size_t end = 0;

    while (end < line.length()) {
      start = end;
      while (start < line.length() && std::isspace(line[start])) {
        start++;
      }

      if (start == line.length()) {
        break;
      }

      end = start;
      while (end < line.length() && !std::isspace(line[end])) {
        end++;
      }

      std::reverse(line.begin() + start, line.begin() + end);
    }

    std::cout << line << std::endl;
  }

  return 0;
}
