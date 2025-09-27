// main.cpp
#include "MyVector.h" // 引用我們新的 MyVector.h 標頭檔
#include <iostream>
#include <string>     // 為了使用 std::string

int main() {
    std::cout << "--- Testing MyVector<int> ---" << std::endl;
    MyVector<int> int_vec;
    int_vec.push_back(10);
    int_vec.push_back(20);
    int_vec.push_back(30);

    std::cout << "Initial int_vec[1] = " << int_vec[1] << std::endl;
    int_vec[1] = 99; // 測試 non-const operator[] 修改功能
    std::cout << "Modified int_vec[1] = " << int_vec[1] << std::endl;

    std::cout << "\n--- Testing MyVector<std::string> ---" << std::endl;
    MyVector<std::string> string_vec;
    string_vec.push_back("Hello");
    string_vec.push_back("World");

    std::cout << "string_vec elements: ";
    for (size_t i = 0; i < string_vec.size(); ++i) {
        std::cout << string_vec[i] << " "; // 測試 const operator[] 讀取功能
    }
    std::cout << std::endl;

    return 0;
}
