#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <unordered_map>
#include "Product.h" // 引入我們剛才定義的 Product 結構

class Shop {
public:
    // 公開的成員函式，是外界與商店互動的介面
    void run(); // 啟動商店的主迴圈

private:
    // 私有的成員變數與函式，只能在 Shop 類別內部使用
    std::unordered_map<std::string, Product> products;

    void setup(); // 處理開店準備的邏輯
    
    // 將每個操作都變成一個私有的輔助函式，讓 run() 函式更簡潔
    void handle_add_order();
    void handle_query_product();
    void handle_delete_product();
    void handle_add_product();
    void print_sales_report();
};

#endif // SHOP_H