#include "Game.h"

Game::Game() 
    : _window(sf::VideoMode(800, 600), "SFML Asteroids | CS106L") 
{
    // _player 會在這裡自動呼叫它自己的預設建構函式
}

void Game::run() {
    sf::Clock clock;
    while (_window.isOpen()) {
        sf::Time dt = clock.restart(); // 計算從上一幀到現在的時間差 (delta time)
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
    }
    // 玩家的移動控制被放在 update 函式中，因為 isKeyPressed 檢查的是「持續按住」的狀態
}

void Game::update(sf::Time dt) {
    // 我們在每一幀都呼叫 player 的 update 函式，並傳入時間差
    _player.update(dt);
}

void Game::render() {
    _window.clear(); // 用預設的黑色清空畫面

    // 呼叫 player 的 draw 函式把自己畫出來
    _player.draw(_window);

    _window.display();
}
