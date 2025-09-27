#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Pathfinding.h"

// 全域遊戲常數
const int GRID_SIZE = 10;
const int WINDOW_SIZE = 500;
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;

class Game {
public:
    Game();
    void run();

private:
    // 主迴圈函式
    void processEvents();
    void update(); // <--- 新增：處理遊戲邏輯更新
    void render();

    // 初始化函式
    void initGrid();
    void initPlayer();

    // 事件處理
    void handleMouseClick(sf::Vector2i mousePos);

    // A* 演算法主函式
    std::vector<Node> aStarSearch(sf::Vector2i startPos, sf::Vector2i endPos);

    // A* 輔助函式
    bool isValid(int r, int c);
    bool isUnblocked(int r, int c);
    int calculateHValue(int r, int c, int destR, int destC);
    std::vector<Node> reconstructPath(Node* goalNode);
    void drawPath(); // <--- 之前的步驟中已加入

    // --- 私有成員變數 ---
    sf::RenderWindow mWindow;
    std::vector<std::vector<sf::RectangleShape>> mGrid;
    sf::RectangleShape mPlayer;
    sf::Vector2i mPlayerPos;
    sf::Vector2i mTargetPos;
    std::vector<Node> mPath;

    // --- 新增：動畫相關的成員變數 ---
    sf::Clock mAnimationClock;
    float mAnimationTimeStep;
    size_t mCurrentPathIndex;
    bool mIsAnimating;
};
