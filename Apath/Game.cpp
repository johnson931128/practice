#include "Game.h"
#include <iostream>

// Constructor 的實作
Game::Game() 
: mWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "A* Pathfinding"), 
  mTargetPos(-1, -1)
{
    mWindow.setFramerateLimit(60);
    initGrid();
    initPlayer();
}

void Game::initGrid() {
    mGrid.resize(GRID_SIZE, std::vector<sf::RectangleShape>(GRID_SIZE));
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            mGrid[i][j].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            mGrid[i][j].setPosition(i * CELL_SIZE, j * CELL_SIZE);
            mGrid[i][j].setFillColor(sf::Color(30, 30, 30));
            mGrid[i][j].setOutlineColor(sf::Color(80, 80, 80));
            mGrid[i][j].setOutlineThickness(1.0f);
        }
    }
}

void Game::initPlayer() {
    mPlayer.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    mPlayer.setFillColor(sf::Color::Red);
    mPlayerPos = {GRID_SIZE / 2, GRID_SIZE / 2};
    mPlayer.setPosition(mPlayerPos.x * CELL_SIZE, mPlayerPos.y * CELL_SIZE);
}

void Game::run() {
    while (mWindow.isOpen()) {
        processEvents();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(sf::Mouse::getPosition(mWindow));
            }
        }
    }
}

void Game::handleMouseClick(sf::Vector2i mousePos) {
    int col = mousePos.x / CELL_SIZE;
    int row = mousePos.y / CELL_SIZE;

    if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE) {
        if (mTargetPos.x != -1) {
            mGrid[mTargetPos.x][mTargetPos.y].setFillColor(sf::Color(30, 30, 30));
        }
        mTargetPos = {col, row};
        mGrid[mTargetPos.x][mTargetPos.y].setFillColor(sf::Color::Green);
        std::cout << "New target set at: (" << col << ", " << row << ")\n";
        // --- 1. 當設定新目標時，呼叫 A* 搜尋 ---
        mPath = aStarSearch(mPlayerPos, mTargetPos);
    }
}

void Game::render() {
    mWindow.clear(sf::Color(50, 50, 50));

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            mWindow.draw(mGrid[i][j]);
        }
    }
    mWindow.draw(mPlayer);

    mWindow.display();
}


// --- 2. 在檔案底部新增 aStarSearch 的實作 ---
std::vector<Node> Game::aStarSearch(sf::Vector2i startPos, sf::Vector2i endPos) {
    std::cout << "A* search started from (" << startPos.x << "," << startPos.y 
              << ") to (" << endPos.x << "," << endPos.y << ")\n";

    // 演算法的具體邏輯將在下一步加入
    // 現在，我們先回傳一個空的路徑
    return {}; 
}
