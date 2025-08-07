#include "Game.h"
#include "Config.h"

Game::Game()
    : mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Snake | CS106L") 
{
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
        else if (event.type == sf::Event::KeyPressed) {
            // 這部分邏輯和之前一樣
            switch (event.key.code) {
                case sf::Keyboard::W: mSnake.setDirection(Direction::Up); break;
                case sf::Keyboard::S: mSnake.setDirection(Direction::Down); break;
                case sf::Keyboard::A: mSnake.setDirection(Direction::Left); break;
                case sf::Keyboard::D: mSnake.setDirection(Direction::Right); break;
                default: break;
            }
        }
    }
}

void Game::update() {
    // 【關鍵】確保蛇先移動，再檢查碰撞
    if (mSnake.isAlive()) {
        mSnake.update();
    }
    checkCollision();
}

void Game::render() {
    mWindow.clear(sf::Color::Black);
    
    // ... 繪製格線的程式碼 ...
    for (size_t x = 0; x < static_cast<size_t>(WINDOW_WIDTH / GRID_SIZE); ++x) {
        for (size_t y = 0; y < static_cast<size_t>(WINDOW_HEIGHT / GRID_SIZE); ++y) {
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
    
    mWindow.display();
}

void Game::checkCollision() {
    if (!mSnake.isAlive()) return;

    // 【關鍵】檢查蛇頭和食物的位置是否完全重合
    if (mSnake.getHeadPosition() == mFood.getPosition()) {
        mSnake.grow();
        mFood.respawn();
    }
}
