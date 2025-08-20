#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Pathfinding.h"

// 全域遊戲常數 (不變)
const int GRID_SIZE = 10;
const int WINDOW_SIZE = 500;
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;

class Game {
public:
    Game();
    void run();

private:
    // --- 函式宣告 (不變) ---
    void processEvents();
    void handleMouseClick(sf::Vector2i mousePos);
    void render();
    void initGrid();
    void initPlayer();
    std::vector<Node> aStarSearch(sf::Vector2i startPos, sf::Vector2i endPos);

    // --- A* 輔助函式 (不變) ---
    bool isValid(int r, int c);
    bool isUnblocked(int r, int c);
    int calculateHValue(int r, int c, int destR, int destC);
    std::vector<Node> reconstructPath(Node* goalNode);

    // --- 新增：繪製路徑的函式宣告 ---
    void drawPath();

    // --- 私有成員變數 (不變) ---
    sf::RenderWindow mWindow;
    std::vector<std::vector<sf::RectangleShape>> mGrid;
    sf::RectangleShape mPlayer;
    sf::Vector2i mPlayerPos;
    sf::Vector2i mTargetPos;
    std::vector<Node> mPath;
};
