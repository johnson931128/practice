#pragma once
#include "Snake.h"
#include <SFML/Graphics.hpp>
#include "Food.h"

class Game {
public:
    // 建構函式，負責初始化遊戲
    Game();
    // 主迴圈，負責運行整個遊戲
    void run();

private:
    // 將遊戲迴圈的三個核心階段拆分成獨立函式
    void processEvents();
    void update();
    void render();
    void checkCollision();

    // 私有成員變數，封裝了遊戲的狀態
    sf::RenderWindow mWindow; // 遊戲視窗
    // 之後還會加入蛇、食物等...
    Snake mSnake;
    Food mFood;
    sf::Clock mClock;
};
