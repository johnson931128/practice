#include "Game.h"
#include <iostream>

// A* 演算法需要的標頭檔
#include <queue>
#include <cmath>
#include <algorithm>

// Game::Game() 的實作 (Constructor)
Game::Game() 
: mWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "A* Pathfinding"), 
  mTargetPos(-1, -1),
  mAnimationTimeStep(0.05f), // 設定每步動畫間隔為 0.05 秒
  mCurrentPathIndex(0),
  mIsAnimating(false)
{
    mWindow.setFramerateLimit(60);
    initGrid();
    initPlayer();
}

// initGrid() 的實作
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

// initPlayer() 的實作
void Game::initPlayer() {
    mPlayer.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    mPlayer.setFillColor(sf::Color::Red);
    mPlayerPos = {GRID_SIZE / 2, GRID_SIZE / 2};
    mPlayer.setPosition(mPlayerPos.x * CELL_SIZE, mPlayerPos.y * CELL_SIZE);
}

// run() 的實作 (主遊戲迴圈)
void Game::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update(); // 在處理事件後、繪製畫面錢，更新遊戲狀態
        render();
    }
}

// update() 的實作 (動畫邏輯核心)
void Game::update() {
    if (!mIsAnimating) return; // 如果不在動畫狀態，直接返回

    // 檢查距離上次移動是否已超過指定間隔
    if (mAnimationClock.getElapsedTime().asSeconds() > mAnimationTimeStep) {
        // 移動到路徑的下一個節點
        mCurrentPathIndex++;

        // 如果已經走完路徑
        if (mCurrentPathIndex >= mPath.size()) {
            mIsAnimating = false; // 停止動畫
            mPlayerPos = mTargetPos; // 確保玩家最終位置與目標一致
            // 清除路徑和目標的顏色
             mGrid[mTargetPos.x][mTargetPos.y].setFillColor(sf::Color(30, 30, 30));
             for(const auto& node : mPath) {
                mGrid[node.x][node.y].setFillColor(sf::Color(30, 30, 30));
            }
            return;
        }

        // 更新玩家位置並將經過的格子變藍
        const auto& nextNode = mPath[mCurrentPathIndex];
        mPlayerPos = {nextNode.x, nextNode.y};
        mPlayer.setPosition(mPlayerPos.x * CELL_SIZE, mPlayerPos.y * CELL_SIZE);
        
        // 將剛走過的格子（前一個節點）變藍
        const auto& prevNode = mPath[mCurrentPathIndex - 1];
        mGrid[prevNode.x][prevNode.y].setFillColor(sf::Color::Blue);

        mAnimationClock.restart(); // 重置時鐘，準備下一次移動
    }
}


// processEvents() 的實作
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

// handleMouseClick() 的實作
void Game::handleMouseClick(sf::Vector2i mousePos) {
    if (mIsAnimating) return; // 如果正在播放動畫，則不接受新的點擊

    int col = mousePos.x / CELL_SIZE;
    int row = mousePos.y / CELL_SIZE;

    if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE) {
        // 清除舊狀態 (目標和路徑顏色)
        if (mTargetPos.x != -1) {
            mGrid[mTargetPos.x][mTargetPos.y].setFillColor(sf::Color(30, 30, 30));
        }
        for(const auto& node : mPath) {
            mGrid[node.x][node.y].setFillColor(sf::Color(30, 30, 30));
        }

        // 設定新目標
        mTargetPos = {col, row};
        mGrid[mTargetPos.x][mTargetPos.y].setFillColor(sf::Color::Green);
        std::cout << "New target set at: (" << col << ", " << row << ")\n";

        // 計算路徑
        mPath = aStarSearch(mPlayerPos, mTargetPos);

        // 啟動動畫
        if (!mPath.empty()) {
            mIsAnimating = true;
            mCurrentPathIndex = 0;
            mAnimationClock.restart();
        }
    }
}

// render() 的實作
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

// aStarSearch() 的實作
std::vector<Node> Game::aStarSearch(sf::Vector2i startPos, sf::Vector2i endPos) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
    std::vector<std::vector<bool>> closedList(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));
    std::vector<std::vector<Node*>> allNodes(GRID_SIZE, std::vector<Node*>(GRID_SIZE, nullptr));

    Node* startNode = new Node(startPos.y, startPos.x);
    startNode->gCost = 0;
    startNode->hCost = calculateHValue(startPos.y, startPos.x, endPos.y, endPos.x);
    startNode->calculateFCost();
    openList.push(startNode);
    allNodes[startPos.y][startPos.x] = startNode;

    while (!openList.empty()) {
        Node* currentNode = openList.top();
        openList.pop();

        if (currentNode->y == endPos.y && currentNode->x == endPos.x) {
            std::cout << "Path found!\n";
            auto path = reconstructPath(currentNode);
            for (auto& row : allNodes) {
                for (auto* node : row) {
                    if (node) delete node;
                }
            }
            return path;
        }

        if(closedList[currentNode->y][currentNode->x]) continue;
        closedList[currentNode->y][currentNode->x] = true;

        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;

                int neighborY = currentNode->y + dy;
                int neighborX = currentNode->x + dx;

                if (isValid(neighborY, neighborX) && isUnblocked(neighborY, neighborX)) {
                    if(closedList[neighborY][neighborX]) continue;

                    Node* neighborNode = allNodes[neighborY][neighborX];
                    bool isNewNode = false;
                    if (neighborNode == nullptr) {
                        neighborNode = new Node(neighborY, neighborX);
                        allNodes[neighborY][neighborX] = neighborNode;
                        isNewNode = true;
                    }

                    int newGCost = currentNode->gCost + ((dx == 0 || dy == 0) ? 10 : 14); 

                    if (isNewNode || newGCost < neighborNode->gCost) {
                        neighborNode->parent = currentNode;
                        neighborNode->gCost = newGCost;
                        neighborNode->hCost = calculateHValue(neighborY, neighborX, endPos.y, endPos.x);
                        neighborNode->calculateFCost();
                        openList.push(neighborNode);
                    }
                }
            }
        }
    }
    
    std::cout << "Path not found.\n";
    for (auto& row : allNodes) {
        for (auto* node : row) {
            if (node) delete node;
        }
    }
    return {};
}

// 輔助函式的實作
bool Game::isValid(int r, int c) {
    return r >= 0 && r < GRID_SIZE && c >= 0 && c < GRID_SIZE;
}

bool Game::isUnblocked(int r, int c) {
    return true;
}

int Game::calculateHValue(int r, int c, int destR, int destC) {
    int dx = std::abs(c - destC);
    int dy = std::abs(r - destR);
    return 10 * (dx + dy);
}

std::vector<Node> Game::reconstructPath(Node* goalNode) {
    std::vector<Node> path;
    Node* currentNode = goalNode;
    while (currentNode != nullptr) {
        path.push_back(*currentNode);
        currentNode = currentNode->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}
