#pragma once // 防止標頭檔被重複引用

#include <SFML/Graphics.hpp>
#include <vector>
#include "Pathfinding.h"

// --- 全域遊戲常數 ---
// 將這些常數定義在類別外部，讓它們在編譯時期就能被確定
const int GRID_SIZE = 10;
const int WINDOW_SIZE = 500;
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;

class Game {
public:
    // Constructor: 用於初始化遊戲
    Game();

    // 啟動主遊戲迴圈
    void run();

private:
    // --- 私有成員函式 ---
    // 處理事件
    void processEvents();
    // 處理滑鼠點擊
    void handleMouseClick(sf::Vector2i mousePos);
    // 繪製所有物件
    void render();
    // 初始化網格
    void initGrid();
    // 初始化玩家
    void initPlayer();
    
    // --- 2. 宣告 A* 搜尋函式 ---
    std::vector<Node> aStarSearch(sf::Vector2i startPos, sf::Vector2i endPos);
    // --- 私有成員變數 ---
    // 遊戲視窗
    sf::RenderWindow mWindow;
    // 遊戲物件
    std::vector<std::vector<sf::RectangleShape>> mGrid;
    sf::RectangleShape mPlayer;
    // 遊戲狀態
    sf::Vector2i mPlayerPos;
    sf::Vector2i mTargetPos;
    // --- 3. 新增一個變數來儲存路徑 ---
    std::vector<Node> mPath;
};
