#pragma once

#include <deque>
#include <SFML/Graphics.hpp>

enum class Direction { None, Up, Down, Left, Right };

class Snake {
public:
    Snake();
    void update();
    void render(sf::RenderWindow& window);
    void setDirection(Direction dir);
    sf::Vector2f getHeadPosition() const;
    bool isAlive() const;
    void grow();
private:
    std::deque<sf::RectangleShape> mBody;
    Direction mDirection;
    bool mIsAlive;
    bool mGrowPending;
};
