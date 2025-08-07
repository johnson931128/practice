#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

// 定義遊戲狀態
enum class GameState { MainMenu, Playing, GameOver };

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    
    // 輔助函式
    void checkCollision();
    void setupMenu();
    void setupTexts();   // 將所有文字設定集中
    void resetGame();

    sf::RenderWindow mWindow;
    Snake mSnake;
    Food mFood;
    sf::Clock mClock;

    // 狀態與 UI 相關成員
    GameState mGameState;
    sf::Font mFont;
    int mScore;

    sf::Text mTitleText;
    sf::Text mStartText;
    sf::Text mGameOverText;
    sf::Text mScoreText;
};
