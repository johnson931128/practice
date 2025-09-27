#pragma once

#include <SFML/Graphics.hpp>

class Food {
public:
    Food();

    void respawn(); // 重生食物到新的隨機位置
    void render(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape mShape;
};
