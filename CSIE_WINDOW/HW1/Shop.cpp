#include "Shop.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

// Shop::run 是商店的主要運作邏輯
void Shop::run() {
    std::cout << "Welcome to NCKU CSIE Shop" << std::endl;
    
    setup(); // 執行開店準備

    // 商店營運的主迴圈
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

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (option == 1) {
            handle_add_order();
        } else if (option == 2) {
            handle_query_product(); // 已實作
        } else if (option == 3) {
            handle_delete_product(); // 已實作
        } else if (option == 4) {
            handle_add_product(); // 已實作
        } else if (option == 5) {
            break; 
        } else {
            std::cout << "Invalid option, please try again!" << std::endl;
        }
    }

    print_sales_report(); 
}

// Shop::setup
void Shop::setup() {
    std::cout << "Please enter the number of product types for today: ";
    int product_count;
    std::cin >> product_count;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
                if (!(ss >> temp)) {
                    products[name] = {name, price};
                    break;
                }
            }
            std::cout << "Invalid input, please try again!" << std::endl;
        }
    }
    std::cout << "\nShop is ready!" << std::endl;
    std::cout << "========================================" << std::endl;
}

// Shop::handle_add_order 處理新增訂單
void Shop::handle_add_order() {
    std::cout << "Please enter the customer's purchase information (item name, quantity, and customer's payment amount): ";
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);

    std::string item_name;
    int quantity;
    int payment;

    if (!(ss >> item_name >> quantity >> payment)) {
        std::cout << "Invalid input, please try again!" << std::endl;
        return;
    }
    std::string temp;
    if (ss >> temp) {
        std::cout << "Invalid input, please try again!" << std::endl;
        return;
    }
    
    if (products.count(item_name) == 0) {
        std::cout << "Invalid input, please try again! (Item not found)" << std::endl;
        return;
    }
    
    Product& product = products.at(item_name);
    int total_cost = product.price * quantity;

    if (payment < total_cost) {
        std::cout << "Invalid input, please try again! (Payment is not enough)" << std::endl;
        return;
    }

    int change = payment - total_cost;
    std::vector<int> denominations = {1000, 500, 100, 50, 10, 5, 1};
    int remaining_change = change;

    for (int coin : denominations) {
        int count = remaining_change / coin;
        std::cout << "Change " << coin << ": " << count << std::endl;
        remaining_change %= coin;
    }

    product.sales_count += quantity;
    std::cout << "Order completed successfully." << std::endl;
}

// 【本次新增】Shop::handle_query_product
void Shop::handle_query_product() {
    std::cout << "Please choose the query item: ";
    std::string name;
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (products.count(name)) {
        const Product& product = products.at(name);
        std::cout << "Item name: " << product.name 
                  << ", Item price: " << product.price 
                  << ", Count: " << product.sales_count << std::endl;
    } else {
        std::cout << "Item not found!" << std::endl;
    }
}

// 【本次新增】Shop::handle_delete_product
void Shop::handle_delete_product() {
    std::cout << "Please choose the delete item: ";
    std::string name;
    std::cin >> name;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (products.erase(name) > 0) {
        std::cout << "Product '" << name << "' deleted successfully." << std::endl;
    } else {
        std::cout << "Item not found!" << std::endl;
    }
}

// 【本次新增】Shop::handle_add_product
void Shop::handle_add_product() {
    while (true) {
        std::cout << "Please enter the item name and price: ";
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string name;
        int price;

        if (ss >> name >> price) {
            std::string temp;
            if (!(ss >> temp)) {
                if (products.count(name)) {
                    std::cout << "Product '" << name << "' already exists. Please use a different name." << std::endl;
                } else {
                    products[name] = {name, price};
                    std::cout << "Product '" << name << "' added successfully." << std::endl;
                    return;
                }
            }
        }
        std::cout << "Invalid input or product already exists, please try again!" << std::endl;
    }
}

void Shop::print_sales_report() {
    std::cout << "\n===== Sales Report =====\n";
    
    int total_revenue = 0; // 用來累加總營業額

    // 使用 range-based for loop 遍歷 map 中的每一個鍵值對 (key-value pair)
    // const auto& [name, product] 是 C++17 的結構化綁定 (structured binding)
    // 直接將 pair 拆解為 name 和 product 兩個變數，程式碼更易讀
    for (const auto& [name, product] : products) {
        std::cout << product.name << ": " << product.sales_count << std::endl;
        total_revenue += product.price * product.sales_count;
    }

    std::cout << "Total: " << total_revenue << std::endl;
    std::cout << "========================\n";
    std::cout << "Program terminated." << std::endl;
}