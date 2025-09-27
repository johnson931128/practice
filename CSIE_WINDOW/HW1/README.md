### 程式結構與物件導向 (Program Structure & OOP)

* **類別封裝 (Class Encapsulation)**: 我們將所有與商店相關的資料 (`products` map) 和功能 (`handle_add_order`, `setup` 等) 全部封裝在一個 `Shop` 類別中。這使得 `main()` 函式變得非常簡潔，只負責建立物件和啟動程式，這是良好的物件導向設計實踐。
* **介面與實作分離 (Interface/Implementation Separation)**: 我們將程式碼拆分為 `.h` (標頭檔) 和 `.cpp` (實作檔)。
    * `Shop.h` 定義了 `Shop` 類別的「長相」和「能做什麼」(介面)。
    * `Shop.cpp` 則負責實作這些功能的具體細節。
* **標頭檔守衛 (Header Guards)**: 在所有 `.h` 檔案中使用 `#ifndef`, `#define`, `#endif` 來防止重複引用，這是 C++ 專案的標準做法，可以避免許多編譯錯誤。

### 資料結構 (Data Structures)

* [cite_start]**`struct` 的應用**: 我們使用 `struct Product` 來捆綁多個不同型別的資料（名稱、價格、銷售數量），形成一個有意義的資料單元 [cite: 3381, 3389]。這比使用零散的變數來管理商品資訊要清晰得多。
* **`std::unordered_map` 的選擇與應用**:
    * **選擇理由**: 為了能透過商品名稱快速地查找、新增和刪除商品，我們選擇了雜湊表 (Hash Table) 結構的 `std::unordered_map`。它的平均操作時間複雜度為 O(1)，效率極高。
    * **操作**: 我們實際應用了 `unordered_map` 的多個核心功能：
        * 使用 `operator[]` 快速新增或更新項目 (`products[name] = ...`)。
        * 使用 `.count()` 來安全地檢查一個 `key` 是否存在。
        * 使用 `.at()` 來取得已存在的 `value` 的引用，並進行修改。
        * 使用 `.erase()` 來刪除項目。
* **`std::vector` 的應用**: 我們用 `std::vector<int>` 來儲存找零的錢幣面額，並透過迴圈遍歷它來執行演算法。

### 輸入/輸出與流程控制 (I/O & Flow Control)

* **`getline` 與 `stringstream` 組合技**: 這是本次作業處理輸入的核心技巧。為了處理包含空格且 token 數量不固定的輸入，我們：
    1.  用 `std::getline(std::cin, line)` 讀取一整行。
    2.  將 `line` 放入 `std::stringstream`。
    3.  [cite_start]從 `stringstream` 中用 `>>` 逐一解析出需要的資料，並透過檢查後續是否還有資料來判斷 token 數量是否正確 [cite: 3391, 3403]。
* **`cin` 緩衝區問題處理**: 我們學到了在使用 `std::cin >> variable;` 後，必須使用 `std::cin.ignore()` 來清除殘留在緩衝區的換行符，以避免對後續的 `std::getline` 造成干擾。
* **錯誤處理與 `cin.fail()`**: 當使用者在應輸入數字的地方輸入文字時，我們使用 `std::cin.fail()` 來捕捉這個錯誤狀態，並透過 `std::cin.clear()` 和 `std::cin.ignore()` 來重置輸入流，讓程式可以繼續接收新的輸入而不是崩潰。

### 演算法 (Algorithms)

* [cite_start]**貪婪演算法 (Greedy Algorithm)**: 在計算找零時，我們從最大面額的錢幣開始，盡可能多地使用，然後處理剩餘的金額。對於標準錢幣系統，這個方法可以保證使用最少的錢幣總數 [cite: 3415, 3467]。
* **狀態更新**: 在 `handle_add_order()` 中，我們在交易成功後更新 `Product` 物件的 `sales_count`，並在關店時遍歷所有商品計算總營業額。這體現了程式在執行過程中維護和更新其內部「狀態」的邏輯。

### 現代 C++ 語法

* **統一初始化 (Uniform Initialization)**: 我們使用大括號 `{}` 來初始化物件和結構，例如 `products[name] = {name, price};`，這是 C++11 後更安全且通用的初始化方式。
* **範圍 `for` 迴圈 (Range-based `for` loop)**: 在遍歷找零面額的 `vector` 和最終遍歷 `products` map 時，我們都使用了這種更簡潔、不易出錯的迴圈語法。
* **結構化綁定 (Structured Binding)**: 在 `print_sales_report` 中，我們使用 `for (const auto& [name, product] : products)` 直接將 `map` 中的鍵值對拆解成兩個獨立的變數，大幅提升了程式碼的可讀性。