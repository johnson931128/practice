#include "Snake.h"

const float GRID_SIZE = 40.0;
const float WINDOW_WIDTH = 800.0;
const float WINDOW_HEIGHT = 600.0;

Snake::Snake() {
    mDirection = Direction::Right;
    mIsAlive = true;
    mBody.clear();
    for (int i = 0; i < 3; ++i){
        sf::RectangleShape segment;
        segment.setSize(sf::Vector2f(GRID_SIZE - 1, GRID_SIZE - 1));
        segment.setFillColor(sf::Color::Green);
        segment.setPosition(WINDOW_WIDTH / 2 - i * GRID_SIZE, WINDOW_HEIGHT / 2);
        mBody.push_back(segment);
    }
}

void Snake::setDirection(Direction dir) {
    // 防止蛇直接 180 度掉頭
    if (mDirection == Direction::Up && dir == Direction::Down) return;
    if (mDirection == Direction::Down && dir == Direction::Up) return;
    if (mDirection == Direction::Left && dir == Direction::Right) return;
    if (mDirection == Direction::Right && dir == Direction::Left) return;

    mDirection = dir;
}


bool Snake::isAlive() const{
    return mIsAlive;
}


void Snake::update() {
    if (!mIsAlive) return;
    sf::RectangleShape newHead = mBody.front();
    switch (mDirection){
        case Direction::Up:
            newHead.move(0, -GRID_SIZE);
            break;
        case Direction::Down:
            newHead.move(0, GRID_SIZE);
            break;
        case Direction::Right:
            newHead.move(GRID_SIZE, 0);
            break;
        case Direction::Left:
            newHead.move(-GRID_SIZE, 0);
            break;
    }

    sf::Vector2f headPos = newHead.getPosition();
    if (headPos.x < 0 || headPos.x >= WINDOW_WIDTH || headPos.y < 0 || headPos.y >= WINDOW_HEIGHT){mIsAlive = false;return;}
    mBody.push_front(newHead);
    mBody.pop_back();
}


void Snake::render(sf::RenderWindow& window){
    for (const auto& segment : mBody){
        window.draw(segment);
    }
}
