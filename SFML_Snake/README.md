# SFML 貪吃蛇 (SFML_Snake)

這是一個使用 C++17 和 [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org/) 函式庫開發的經典貪吃蛇遊戲。本專案不僅是一個可執行的遊戲，更是對 CS106L 課程中所學 C++ 核心概念的具體實踐與展示。

## 專案目標
1.  **實踐物件導向**: 將遊戲的不同實體（遊戲控制器、蛇、食物）抽象化為獨立的 `class`。
2.  **應用 C++ 核心語法**: 大量使用 CS106L 課程中的重要概念，如 RAII、STL 容器、演算法、Lambda、參考傳遞與 `const` 正確性等。
3.  **掌握遊戲開發基礎**: 實現一個完整的遊戲迴圈、狀態管理與事件處理流程。

---

## 如何編譯與執行

本專案使用 `Makefile` 進行建置，這是一種在 C++ 開發中常見的自動化編譯工具。

**前置需求**:
* C++17 相容的編譯器 (例如 G++)。
* SFML 函式庫 (graphics, window, system)。
    * 在 Ubuntu/Debian 上安裝: `sudo apt-get install libsfml-dev`

**編譯步驟**:
1.  開啟終端機，進入 `SFML_Snake` 目錄。
2.  執行 `make` 指令。

    ```bash
    make
    ```
    * [cite_start]**CS106L 概念連結 (Lecture 15)** [cite: 3396-3399]: `Makefile` 自動化了手動使用 `g++` 編譯多個檔案的繁瑣過程。它定義了 `CXXFLAGS = -std=c++17` 來確保使用 C++17 標準，並透過 `LDFLAGS` 告訴連結器需要 SFML 函式庫，這正是大型專案管理的方式。

**執行遊戲**:
* 編譯成功後，執行 `./snake` 即可啟動遊戲。

    ```bash
    ./snake
    ```

**清理檔案**:
* 若要刪除所有編譯產生的中介檔 (`.o`) 和執行檔，可以執行 `make clean`。

---

## 遊戲操作

* **移動**: `W` (上), `A` (左), `S` (下), `D` (右)。
* **開始/重新開始**: 在主選單或遊戲結束畫面，按下 `Enter` 鍵。

---

## 程式碼架構與 CS106L 概念詳解

本專案遵循物件導向設計，將遊戲的不同部分封裝在各自的類別中，實現了高內聚、低耦合的目標。

### 1. `Game` 類 (遊戲總管)
* **檔案**: `Game.h`, `Game.cpp`
* **職責**: 作為遊戲的引擎，負責管理遊戲視窗、狀態、主迴圈以及所有遊戲物件的互動。

#### 關鍵程式碼分析:
* **`Game::Game()` (建構函式)**
    * **程式碼**: `mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Snake | CS106L")`
    * **CS106L 概念連結 (Lecture 8, 15)**:
        * [cite_start]**類別 (Classes)**[cite: 1731]: 這裡建立了 `Game` 物件。
        * [cite_start]**RAII (Resource Acquisition Is Initialization)**[cite: 3330]: `mWindow`、`mSnake`、`mFood` 等成員變數在 `Game` 物件建構時被自動初始化。當 `Game` 物件的生命週期結束時（例如 `main` 函式結束），其解構函式會被呼叫，並自動觸發所有成員變數的解構函式，釋放它們佔用的資源（如視窗控制代碼、記憶體等）。這完美體現了 RAII 的核心思想：資源的生命週期與物件的生命週期綁定，無需手動 `delete`，極大地增強了程式的穩定性。

* **`Game::run()` (主遊戲迴圈)**
    * **程式碼**: `while (mWindow.isOpen()) { ... timeSinceLastUpdate += mClock.restart(); while (timeSinceLastUpdate > TimePerFrame) { ... update(); } render(); }`
    * **說明**: 這是一個經典的 **固定時間步長 (Fixed Timestep)** 遊戲迴圈。它確保了 `update()`（遊戲邏輯更新）的頻率是固定的，不受 `render()`（畫面繪製）速度的影響，使得遊戲在不同效能的電腦上表現一致。

* **`Game::render()`**
    * **程式碼**: `mFood.render(mWindow); mSnake.render(mWindow);`
    * **CS106L 概念連結 (Lecture 3)**:
        * [cite_start]**傳遞參考 (Pass by Reference)**[cite: 928]: 這裡呼叫 `render` 函式時傳入的是 `mWindow`，而不是它的複本。`sf::RenderWindow` 是一個複雜且龐大的物件，如果進行複製會帶來巨大的效能開銷。透過傳遞參考 (`sf::RenderWindow&`)，`Snake` 和 `Food` 的 `render` 函式可以直接在原始的視窗物件上進行繪製，既高效又符合 C++ 的最佳實踐。

### 2. `Snake` 類 (遊戲主角)
* **檔案**: `Snake.h`, `Snake.cpp`
* **職責**: 封裝蛇的所有行為，包括移動、成長、碰撞檢測等。

#### 關鍵程式碼分析:
* **`std::deque<sf::RectangleShape> mBody;`**
    * **CS106L 概念連結 (Lecture 6)**:
        * [cite_start]**STL 容器 (Containers)** [cite: 1413][cite_start]: 這裡選擇 `std::deque` 而非 `std::vector` 是經過深思熟慮的。蛇的移動需要在頭部新增一節 (`push_front`) 並在尾部移除一節 (`pop_back`)。`std::deque`（雙向佇列）對頭尾兩端的操作都是 O(1) 的常數時間複雜度，效能極高。如果使用 `std::vector`，`push_front` 的操作將是 O(N) 的，因為需要移動所有後續元素，會非常慢 [cite: 1473]。

* **`Snake::update()` (自我碰撞檢測)**
    * **程式碼**: `bool collision = std::any_of(std::next(mBody.begin()), mBody.end(), [&](const sf::RectangleShape& segment){...});`
    * **CS106L 概念連結 (Lecture 7, 10, 11)**:
        * [cite_start]**STL 演算法 (Algorithms)**[cite: 2716]: `std::any_of` 是 `<algorithm>` 中的一個強大工具。它取代了手寫的 for 迴圈，程式碼更簡潔，意圖更明確：檢查範圍內是否有**任何一個**元素滿足條件。
        * [cite_start]**迭代器 (Iterators)**[cite: 1591]: `mBody.begin()` 和 `mBody.end()` 定義了要遍歷的範圍。`std::next()` 則巧妙地將起始點向後移動一個位置，從而排除了蛇頭本身，只檢查蛇頭與身體的碰撞。
        * [cite_start]**Lambda 函式 (Lambdas)** [cite: 2665][cite_start]: `[&](...){...}` 是一個 Lambda 函式，一個可以就地定義的匿名函式。它作為謂詞 (predicate) [cite: 2612] 傳遞給 `std::any_of`。`[&]` 表示以參考方式捕獲所有外部變數，讓我們可以在 Lambda 內部直接存取 `newHead`，極大地提高了程式碼的可讀性和便利性。

* **`sf::Vector2f getHeadPosition() const;`**
    * **CS106L 概念連結 (Lecture 8)**:
        * [cite_start]**`const` 正確性 (Const Correctness)**[cite: 2214]: 函式末尾的 `const` 是一個對編譯器的承諾：此函式不會修改 `Snake` 物件的任何成員變數。這是一個非常重要的 C++ 實踐，它讓編譯器可以進行更多檢查，也讓其他開發者能一眼看出此函式是安全的「唯讀」操作。

### 3. `Food` 類 (遊戲道具)
* **檔案**: `Food.h`, `Food.cpp`
* **職責**: 負責食物的隨機生成與顯示。

#### 關鍵程式碼分析:
* **`Food::respawn()`**
    * **程式碼**: 使用 `std::random_device`, `std::mt19937`, `std::uniform_int_distribution`。
    * **說明**: 這展示了現代 C++ 產生高品質隨機數的標準方法。`std::random_device` 提供一個真正的硬體亂源作為種子，`std::mt19937` 是一個高效的隨機數引擎，而 `std::uniform_int_distribution` 則確保產生的數字在指定範圍內是均勻分佈的。這遠比舊式的 `rand()` 函式更可靠、更專業。

---

## 作者追蹤與更新方向

此專案目前已具備核心功能，但仍有許多可以改進和擴充的地方，方便後續追蹤：

* **程式碼重構**:
    * **資源管理**: `Game.cpp` 中多次載入字型，可優化為在建構函式中只載入一次。更進一步，可以建立一個 `ResourceManager` 類別來統一管理所有資源（字型、圖片、音效）。
    * **狀態模式 (State Pattern)**: 當遊戲邏輯變得更複雜時（例如增加「暫停」狀態），目前的 `switch-case` 會變得臃腫。可以引入狀態設計模式，將每個狀態的邏輯（`update`, `render`, `processEvents`）封裝到獨立的類別中。

* **新功能**:
    * **計分系統**: 增加歷史最高分紀錄，並儲存到檔案中。
    * **難度調整**: 遊戲速度可以隨著分數的增加而提升。
    * **音效**: 加入吃到食物、遊戲結束等音效，提升遊戲體驗。
