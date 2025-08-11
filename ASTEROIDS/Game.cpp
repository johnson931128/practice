#include "Game.h"
#include "Player.h"   // 我們需要引入 Player.h，因為我們要建立 Player
#include "Asteroid.h" // 我們需要引入 Asteroid.h，因為我們要建立 Asteroid

// Game 的建構函式
Game::Game() 
    : _window(sf::VideoMode(800, 600), "SFML Asteroids - Step 2") 
{
    // === 核心修改 1: 在遊戲開始時，動態建立物件 ===

    // 1. 建立一個玩家
    // std::make_unique<Player>() 會在記憶體中建立一個新的 Player 物件，
    // 並用一個 unique_ptr 智慧指標把它包起來。
    auto player = std::make_unique<Player>();

    // std::move() 是一個 C++11 的特性，它能高效地將 player 指標的「所有權」
    // 「移動」到我們的 _gameObjects 容器中。移動後，原來的 player 指標就變空了。
    _gameObjects.push_back(std::move(player));

    // 2. 建立 5 顆小行星
    for (int i = 0; i < 5; ++i) {
        // 我們直接在 push_back 的參數中建立新的小行星
        // 並將視窗大小傳給它，讓它知道該在哪裡生成
        _gameObjects.push_back(std::make_unique<Asteroid>(_window.getSize()));
    }
}

// 主遊戲迴圈 (這裡不需要改變)
void Game::run() {
    sf::Clock clock;
    while (_window.isOpen()) {
        sf::Time dt = clock.restart();
        processEvents();
        update(dt);
        render();
    }
}

// 事件處理 (這裡不需要改變)
void Game::processEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
    }
}

// 更新所有遊戲物件的狀態
void Game::update(sf::Time dt) {
    // === 核心修改 2: 更新所有物件 ===
    
    // 我們使用 C++11 的「範圍 for 迴圈」(range-based for loop)
    // 來遍歷 _gameObjects 容器中的每一個物件。
    // "auto&" 代表「自動推斷型別，並使用引用（&）以避免不必要的複製」
    for (auto& gameObject : _gameObjects) {
        // 這就是「多型」的威力！
        // 我們不需要知道 gameObject 到底是 Player 還是 Asteroid，
        // 只需要呼叫 update()，C++ 就會自動根據物件的實際型別，
        // 去執行正確的 update() 版本。
        gameObject->update(dt);
    }
}

// 繪製所有遊戲物件
void Game::render() {
    _window.clear();

    // === 核心修改 3: 繪製所有物件 ===

    // 同樣地，我們遍歷所有物件
    for (const auto& gameObject : _gameObjects) {
        // 並呼叫它們各自的 draw() 函式
        // const auto& 的 const 代表我們在繪製過程中，保證不會修改到物件
        gameObject->draw(_window);
    }

    _window.display();
}
