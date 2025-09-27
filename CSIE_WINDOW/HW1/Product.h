#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

// 產品的資料結構
struct Product {
    std::string name;
    int price;
    int sales_count = 0;
};

#endif // PRODUCT_H