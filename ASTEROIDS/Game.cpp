#include "Game.h"
#include "Player.h"
#include "Asteroid.h"
// 我們不再需要在此 #include "Bullet.h"，因為 Game 不直接建立 Bullet

Game::Game() 
    : _window(sf::VideoMode(800, 600), "SFML Asteroids - Pew Pew!") 
{
    // 建立一個玩家
    _gameObjects.push_back(std::make_unique<Player>());

    // 建立 5 顆小行星
    for (int i = 0; i < 5; ++i) {
        _gameObjects.push_back(std::make_unique<Asteroid>(_window.getSize()));
    }
}

Game::~Game() = default;

void Game::run() {
    sf::Clock clock;
    while (_window.isOpen()) {
        sf::Time dt = clock.restart();
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
}

void Game::update(sf::Time dt) {
    // === 核心修改：接收新產生的物件 ===

    // 1. 建立一個「等候區」來暫存這一幀新產生的所有物件
    std::vector<std::unique_ptr<GameObject>> newObjects;

    // 2. 遍歷所有現存的物件，更新它們，並接收新物件
    for (auto& gameObject : _gameObjects) {
        // 呼叫物件的 update，並接收可能的回傳值
        auto newObject = gameObject->update(dt);

        // 如果回傳的不是空指標，代表有新物件（子彈）產生
        if (newObject) {
            // 將這個新物件的所有權「移動」到我們的等候區 newObjects 中
            newObjects.push_back(std::move(newObject));
        }
    }

    // 3. 【重要】在所有更新都完成後，才將等候區的物件加入到主列表中
    for (auto& newObject : newObjects) {
        _gameObjects.push_back(std::move(newObject));
    }
}

void Game::render() {
    _window.clear();

    for (const auto& gameObject : _gameObjects) {
        gameObject->draw(_window);
    }

    _window.display();
}
