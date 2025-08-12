#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class GameObject; 

class Game {
public:
    Game();
    ~Game(); // <--- 新增：手動宣告解構函式

    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();

    sf::RenderWindow _window;
    std::vector<std::unique_ptr<GameObject>> _gameObjects;
};
