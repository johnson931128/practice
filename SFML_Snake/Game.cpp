#include "Game.h"
#include "Config.h"
#include <iostream>
#include <string> // 為了 std::to_string

Game::Game()
    : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Snake | CS106L"),
      mGameState(GameState::MainMenu),
      mScore(0)
{
    // 載入字型並設定所有文字
    if (!mFont.loadFromFile("font.ttf")) {
        std::cerr << "Error: Could not load font.ttf" << std::endl;
    }
    setupTexts();
    resetGame();
}

void Game::setupTexts() {
    // --- 主選單文字 ---
    mTitleText.setFont(mFont);
    mTitleText.setString("SNAKE");
    mTitleText.setCharacterSize(80);
    sf::FloatRect titleBounds = mTitleText.getLocalBounds();
    mTitleText.setOrigin(titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);
    mTitleText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 4.0f);

    mStartText.setFont(mFont);
    mStartText.setString("Press Enter to Start");
    mStartText.setCharacterSize(40);
    sf::FloatRect startBounds = mStartText.getLocalBounds();
    mStartText.setOrigin(startBounds.left + startBounds.width / 2.0f, startBounds.top + startBounds.height / 2.0f);
    mStartText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);

    // --- 分數文字 ---
    mScoreText.setFont(mFont);
    mScoreText.setCharacterSize(30);
    mScoreText.setFillColor(sf::Color::White);
    mScoreText.setPosition(20, 10); // 左上角

    // --- 遊戲結束文字 ---
    mGameOverText.setFont(mFont);
    mGameOverText.setString("GAME OVER\nPress Enter to Restart");
    mGameOverText.setCharacterSize(60);
    mGameOverText.setFillColor(sf::Color::Red);
    sf::FloatRect gameOverBounds = mGameOverText.getLocalBounds();
    mGameOverText.setOrigin(gameOverBounds.left + gameOverBounds.width / 2.0f, gameOverBounds.top + gameOverBounds.height / 2.0f);
    mGameOverText.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
}

void Game::resetGame() {
    mSnake = Snake(); // 建立一條全新的蛇
    mFood.respawn();
    mScore = 0;
    mScoreText.setString("Score: " + std::to_string(mScore));
}

void Game::run() {
    const sf::Time TimePerFrame = sf::seconds(0.1f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    while (mWindow.isOpen()) {
        processEvents();
        timeSinceLastUpdate += mClock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update();
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }

        switch (mGameState) {
            case GameState::MainMenu:
            case GameState::GameOver: // 主選單和結束畫面有相同的控制邏輯
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    resetGame();
                    mGameState = GameState::Playing;
                }
                break;
            case GameState::Playing:
                if (event.type == sf::Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::W: mSnake.setDirection(Direction::Up); break;
                        case sf::Keyboard::S: mSnake.setDirection(Direction::Down); break;
                        case sf::Keyboard::A: mSnake.setDirection(Direction::Left); break;
                        case sf::Keyboard::D: mSnake.setDirection(Direction::Right); break;
                        default: break;
                    }
                }
                break;
        }
    }
}

void Game::update() {
    if (mGameState != GameState::Playing) return;

    if (mSnake.isAlive()) {
        mSnake.update();
        checkCollision();
    } else {
        // 如果蛇在這一幀死掉，就切換到遊戲結束狀態
        mGameState = GameState::GameOver;
    }
}

void Game::render() {
    mWindow.clear(sf::Color::Black);

    switch (mGameState) {
        case GameState::MainMenu:
            mWindow.draw(mTitleText);
            mWindow.draw(mStartText);
            break;
        case GameState::Playing:
        case GameState::GameOver: // GameOver 時也要畫遊戲場景
            // 繪製格線...
            for (size_t x = 0; x < static_cast<size_t>(WINDOW_WIDTH/GRID_SIZE); ++x) {
                for (size_t y = 0; y < static_cast<size_t>(WINDOW_HEIGHT/GRID_SIZE); ++y) {
                    sf::RectangleShape cell(sf::Vector2f(GRID_SIZE, GRID_SIZE));
                    cell.setPosition(x * GRID_SIZE, y * GRID_SIZE);
                    cell.setFillColor(sf::Color(20, 20, 20));
                    cell.setOutlineThickness(1.f);
                    cell.setOutlineColor(sf::Color(40, 40, 40));
                    mWindow.draw(cell);
                }
            }
            mFood.render(mWindow);
            mSnake.render(mWindow);
            mWindow.draw(mScoreText);

            if (mGameState == GameState::GameOver) {
                mWindow.draw(mGameOverText); // 在遊戲畫面上方疊加結束文字
            }
            break;
    }
    
    mWindow.display();
}

void Game::checkCollision() {
    if (!mSnake.isAlive()) return;

    if (mSnake.getHeadPosition() == mFood.getPosition()) {
        mSnake.grow();
        mFood.respawn();
        mScore++;
        mScoreText.setString("Score: " + std::to_string(mScore));
    }
}
