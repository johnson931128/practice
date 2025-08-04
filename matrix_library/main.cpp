#include <iostream>
#include <string>
#include "Matrix.h"

// ===== 美化輸出用的輔助工具 =====

// 定義一些 ANSI 顏色代碼，讓終端機輸出有顏色
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[1;32m"; // 粗體綠色
const std::string YELLOW = "\033[1;33m"; // 粗體黃色
const std::string CYAN = "\033[1;36m"; // 粗體青色

// 一個方便印出標題的函式
void print_header(const std::string& title) {
    std::cout << "\n" << GREEN << "===== " << title << " =====" << RESET << std::endl;
}

// 使用 using 給我們常用的型別一個簡潔的別名
using IntMatrix = Matrix<int>;

// ===== 各功能測試函式 =====

void test_initialization_and_access() {
    print_header("測試：矩陣初始化與存取");

    IntMatrix m(3, 4);
    for (size_t r = 0; r < m.getRows(); ++r) {
        for (size_t c = 0; c < m.getCols(); ++c) {
            m.at(r, c) = r * 10 + c;
        }
    }

    std::cout << YELLOW << "矩陣初始內容：" << RESET << std::endl;
    std::cout << m << std::endl;

    std::cout << YELLOW << "將 m.at(1, 1) 設定為 99..." << RESET << std::endl;
    m.at(1, 1) = 99;
    std::cout << m << std::endl;
}

void test_exception_handling() {
    print_header("測試：邊界檢查與例外處理");
    IntMatrix m(2, 2); 
    std::cout << YELLOW << "嘗試存取無效索引 m.at(10, 10)..." << RESET << std::endl;
    try {
        m.at(10, 10) = 0;
    } catch (const std::out_of_range& e) {
        std::cout << "成功捕捉到例外: " << CYAN << e.what() << RESET << std::endl;
    }
}

void test_addition() {
    print_header("測試：矩陣加法");
    IntMatrix m1(2, 3);
    IntMatrix m2(2, 3);

    for (size_t r = 0; r < 2; ++r) {
        for (size_t c = 0; c < 3; ++c) {
            m1.at(r, c) = r * 10 + c;
            m2.at(r, c) = 100;
        }
    }

    std::cout << YELLOW << "矩陣 m1:" << RESET << std::endl << m1;
    std::cout << YELLOW << "矩陣 m2:" << RESET << std::endl << m2;

    IntMatrix sum = m1 + m2;
    std::cout << YELLOW << "m1 + m2 的結果:" << RESET << std::endl << sum;
    
    IntMatrix wrong_size_matrix(3, 2);
    std::cout << YELLOW << "\n嘗試將 2x3 矩陣與 3x2 矩陣相加..." << RESET << std::endl;
    try {
        IntMatrix bad_sum = m1 + wrong_size_matrix;
    } catch (const std::invalid_argument& e) {
        std::cout << "成功捕捉到例外: " << CYAN << e.what() << RESET << std::endl;
    }
}

// 【新增的測試函式】
void test_copy_semantics() {
    print_header("測試：複製建構與賦值 (深複製)");
    IntMatrix m1(2, 2);
    m1.at(0, 0) = 1; m1.at(0, 1) = 2;
    m1.at(1, 0) = 3; m1.at(1, 1) = 4;

    std::cout << YELLOW << "--- 測試複製建構函式 ---" << RESET << std::endl;
    IntMatrix m1_copy = m1; // 呼叫複製建構函式
    m1_copy.at(0, 0) = 999; // 修改複本

    std::cout << YELLOW << "原始矩陣 m1 (應不受影響):" << RESET << std::endl << m1;
    std::cout << YELLOW << "複本矩陣 m1_copy (at(0,0) 應為 999):" << RESET << std::endl << m1_copy;

    std::cout << YELLOW << "\n--- 測試複製賦值運算子 ---" << RESET << std::endl;
    IntMatrix m2_copy(1, 1); // 建立一個不同大小的矩陣
    std::cout << YELLOW << "賦值前的 m2_copy:" << RESET << std::endl << m2_copy;
    m2_copy = m1; // 呼叫複製賦值運算子
    std::cout << YELLOW << "賦值後的 m2_copy (應與 m1 相同):" << RESET << std::endl << m2_copy;
}


// 主函式現在多了一個測試呼叫
int main() {
    test_initialization_and_access();
    test_exception_handling();
    test_addition();
    test_copy_semantics(); // 【新增的呼叫】

    std::cout << std::endl;
    return 0;
}
