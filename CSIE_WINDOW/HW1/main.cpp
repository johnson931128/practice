#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <limits>

struct Product {
    std::string name;
    int price;
    int sales_count = 0;
};

int main() {
    std::cout << "Welcome to NCKU CSIE Shop" << std::endl;

    // ==================== 開店準備階段 ====================
    int product_count;
    std::cout << "Please enter the number of product types for today: ";
    std::cin >> product_count;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::unordered_map<std::string, Product> products;

    for (int i = 0; i < product_count; ++i) {
        while (true) {
            std::cout << "Please enter the name and price of the item " << i + 1 << ": ";
            std::string line;
            std::getline(std::cin, line);

            std::stringstream ss(line);
            std::string name;
            int price;
            
            if (ss >> name >> price) {
                std::string temp;
                if (ss >> temp) {
                    std::cout << "Invalid input, please try again!" << std::endl;
                } else {
                    products[name] = {name, price};
                    break;
                }
            } else {
                std::cout << "Invalid input, please try again!" << std::endl;
            }
        }
    }

    std::cout << "\nShop is ready!" << std::endl;
    std::cout << "========================================" << std::endl;

    // ==================== 商店營運階段 ====================
    while (true) {
        std::cout << "\nPlease input option:\n"
                  << "1: Add an order\n"
                  << "2: Query a product\n"
                  << "3: Delete a product\n"
                  << "4: Add a new product\n"
                  << "5: Close shop\n"
                  << "> ";
        
        int option;
        std::cin >> option;

        // 檢查 cin 是否因為無效輸入 (例如輸入文字) 而進入錯誤狀態
        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear(); // 清除錯誤旗標
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除緩衝區
            continue; // 繼續下一次迴圈
        }
        
        // 再次清除輸入緩衝區，為後續的 getline 做準備
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (option == 1) {
            std::cout << "[Info] Function 'Add an order' will be implemented soon." << std::endl;
        } else if (option == 2) {
            std::cout << "[Info] Function 'Query a product' will be implemented soon." << std::endl;
        } else if (option == 3) {
            std::cout << "[Info] Function 'Delete a product' will be implemented soon." << std::endl;
        } else if (option == 4) {
            std::cout << "[Info] Function 'Add a new product' will be implemented soon." << std::endl;
        } else if (option == 5) {
            std::cout << "[Info] Closing shop..." << std::endl;
            break; // 跳出 while 迴圈
        } else {
            std::cout << "Invalid option, please try again!" << std::endl;
        }
    }

    // 關店後的總結報告 (我們稍後會實作這裡)
    std::cout << "\n===== Sales Report =====\n";
    std::cout << "Program terminated." << std::endl;

    return 0;
}