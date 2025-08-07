#include "Game.h"

// Game 建構函式：使用成員初始化列表來建立視窗
Game::Game()
    : mWindow(sf::VideoMode(800, 600), "SFML Snake | CS106L") 
{
    // 這裡可以進行其他的初始化
}

// 遊戲主迴圈
// 在 Game.cpp 裡找到 Game::run() 函式，然後用下面的版本替換掉它

void Game::run() {
    // 設定遊戲邏輯更新的固定時間間隔
    const sf::Time TimePerFrame = sf::seconds(0.1f); // 每 0.1 秒更新一次
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // mClock 在 Game 的建構函式被建立時就已經開始計時了
    
    while (mWindow.isOpen()) {
        // 處理事件
        processEvents();

        // 累加自上次迴圈以來經過的時間
        timeSinceLastUpdate += mClock.restart();

        // 如果累積的時間超過了我們的固定間隔，就更新遊戲邏輯
        while (timeSinceLastUpdate > TimePerFrame) {
            // 從累積時間中減去一個間隔
            timeSinceLastUpdate -= TimePerFrame;
            
            // 處理事件（再次呼叫以避免錯過輸入）
            processEvents();
            
            // 執行一次遊戲邏輯更新
            update();
        }

        // 每一輪迴圈都重新繪製畫面
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
        // 當有鍵盤按鍵被按下時
        else if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W:
                    mSnake.setDirection(Direction::Up);
                    break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S:
                    mSnake.setDirection(Direction::Down);
                    break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A:
                    mSnake.setDirection(Direction::Left);
                    break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D:
                    mSnake.setDirection(Direction::Right);
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::update() {
    // 只有當蛇還活著的時候才更新牠的狀態
    if (mSnake.isAlive()) {
        mSnake.update();
    }
}

// ...

// 繪製所有遊戲物件到畫面上
void Game::render() {
    mWindow.clear(sf::Color::Black);

    // --- 繪製格線 ---
    const int gridSize = 40;
    for (size_t x = 0; x < mWindow.getSize().x / gridSize; ++x) {
        for (size_t y = 0; y < mWindow.getSize().y / gridSize; ++y) {
            sf::RectangleShape cell(sf::Vector2f(gridSize, gridSize));
            cell.setPosition(x * gridSize, y * gridSize);
            cell.setFillColor(sf::Color(20, 20, 20)); // 深灰色
            cell.setOutlineThickness(1.f);
            cell.setOutlineColor(sf::Color(40, 40, 40)); // 更深的灰色
            mWindow.draw(cell);
        }
    }
    mSnake.render(mWindow);
    mWindow.display();
}
