#pragma once
#include <SFML/Graphics.hpp>
#include <vector>     //  <--- 新增：為了使用 std::vector
#include <memory>     //  <--- 新增：為了使用 std::unique_ptr

// 向前宣告 (Forward Declaration)，告訴 Game.h 有一個類別叫 GameObject
// 這樣我們就不用在這裡 #include "GameObject.h"，可以加快編譯速度
class GameObject;

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();

    sf::RenderWindow _window;

    // 這是核心修改！
    // 我們現在用一個 vector 來儲存指向所有遊戲物件的「智慧指標」
    std::vector<std::unique_ptr<GameObject>> _gameObjects;
};
