#include "Game.h"
#include "Player.h"
#include "Asteroid.h"
#include <cmath>     // <--- 新增：為了計算距離 (sqrt)
#include <algorithm> // <--- 新增：為了使用 std::remove_if

// 輔助函式：計算兩個點之間的距離
float distance(sf::Vector2f p1, sf::Vector2f p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

Game::Game() 
    : _window(sf::VideoMode(800, 600), "Asteroids - The Final Chapter!") 
{
    _gameObjects.push_back(std::make_unique<Player>());
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
    // 1. 更新物件位置 & 接收新物件
    std::vector<std::unique_ptr<GameObject>> newObjects;
    for (auto& obj : _gameObjects) {
        auto newObj = obj->update(dt);
        if (newObj) {
            newObjects.push_back(std::move(newObj));
        }
    }

    // 2. 【全新】處理碰撞偵測
    // 使用巢狀迴圈，讓每個物件都跟它後面的物件比對一次
    for (size_t i = 0; i < _gameObjects.size(); ++i) {
        for (size_t j = i + 1; j < _gameObjects.size(); ++j) {
            auto& obj1 = _gameObjects[i];
            auto& obj2 = _gameObjects[j];

            // 計算兩個物件的距離
            float dist = distance(obj1->getPosition(), obj2->getPosition());

            // 如果距離小於半徑和，代表發生碰撞
            if (dist < obj1->getRadius() + obj2->getRadius()) {
                // 檢查碰撞類型
                if ((obj1->getType() == "Asteroid" && obj2->getType() == "Bullet") ||
                    (obj1->getType() == "Bullet" && obj2->getType() == "Asteroid")) {
                    obj1->destroy();
                    obj2->destroy();
                }
                
                if ((obj1->getType() == "Asteroid" && obj2->getType() == "Player") ||
                    (obj1->getType() == "Player" && obj2->getType() == "Asteroid")) {
                    // 為了遊戲體驗，這裡只銷毀小行星，玩家暫時是無敵的
                    // 如果想讓玩家也被銷毀，可以取消下面這行的註解
                    // obj2->getType() == "Player" ? obj2->destroy() : obj1->destroy();
                    obj1->getType() == "Asteroid" ? obj1->destroy() : obj2->destroy();
                }
            }
        }
    }

    // 3. 將新產生的物件加入主列表
    for (auto& newObj : newObjects) {
        _gameObjects.push_back(std::move(newObj));
    }

    // 4. 【全新】移除所有被標記為 'dead' 的物件
    // std::remove_if 會將所有「不符合」條件的元素（也就是 isAlive() == true 的）往前移動，
    // 並回傳一個指向「垃圾區」開頭的迭代器。
    auto it = std::remove_if(_gameObjects.begin(), _gameObjects.end(), 
                             [](const auto& obj) { return !obj->isAlive(); });

    // vector::erase 會將從迭代器位置到結尾的所有元素（也就是我們的垃圾區）真正地從 vector 中刪除。
    _gameObjects.erase(it, _gameObjects.end());
}


void Game::render() {
    _window.clear();
    for (const auto& gameObject : _gameObjects) {
        gameObject->draw(_window);
    }
    _window.display();
}
