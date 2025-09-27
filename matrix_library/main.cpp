#include <iostream>
#include <string>
#include <utility> // 為了 std::move
#include "Matrix.h"

// ... (美化輸出的輔助工具和 using IntMatrix 不變) ...
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[1;32m";
const std::string YELLOW = "\033[1;33m";
const std::string CYAN = "\033[1;36m";

void print_header(const std::string& title) {
    std::cout << "\n" << GREEN << "===== " << title << " =====" << RESET << std::endl;
}

using IntMatrix = Matrix<int>;

// ... (之前的 test_... 函式不變) ...
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
}

void test_copy_semantics() {
    print_header("測試：複製建構與賦值 (深複製)");
    IntMatrix m1(2, 2);
    m1.at(0, 0) = 1; m1.at(0, 1) = 2;
    m1.at(1, 0) = 3; m1.at(1, 1) = 4;

    std::cout << YELLOW << "\n--- 測試複製建構函式 ---" << RESET << std::endl;
    IntMatrix m1_copy = m1;
    m1_copy.at(0, 0) = 999; 

    std::cout << YELLOW << "原始矩陣 m1 (應不受影響):" << RESET << std::endl << m1;
    std::cout << YELLOW << "複本矩陣 m1_copy (at(0,0) 應為 999):" << RESET << std::endl << m1_copy;
}

// 【新增的測試函式】
void test_move_semantics() {
    print_header("測試：移動語意 (資源竊取)");
    
    std::cout << YELLOW << "\n--- 測試移動建構函式 (來自 operator+ 的臨時物件) ---" << RESET << std::endl;
    IntMatrix m1(2, 2);
    m1.at(0, 0) = 1; m1.at(1, 1) = 1;
    IntMatrix m2(2, 2);
    m2.at(0, 0) = 5; m2.at(1, 1) = 5;
    
    // operator+ 會回傳一個臨時矩陣(右值)，sum 會透過「移動建構函式」接收它的資源
    IntMatrix sum = m1 + m2;
    std::cout << YELLOW << "Sum 矩陣:" << RESET << std::endl << sum;

    std::cout << YELLOW << "\n--- 測試移動賦值運算子 (使用 std::move) ---" << RESET << std::endl;
    std::cout << YELLOW << "移動前的 sum:" << RESET << std::endl << sum;
    IntMatrix moved_to = std::move(sum); // 強制移動
    std::cout << YELLOW << "移動後的 sum (應為空殼):" << RESET << std::endl << sum;
    std::cout << YELLOW << "接收移動結果的 moved_to:" << RESET << std::endl << moved_to;
}

int main() {
    test_initialization_and_access();
    test_copy_semantics();
    test_move_semantics(); // 【新增的呼叫】
    
    std::cout << "\n[INFO] Main function is ending. All matrices will be destructed now." << std::endl;
    return 0;
}
