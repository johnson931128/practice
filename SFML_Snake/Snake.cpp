#include "Snake.h"
#include "Config.h"


Snake::Snake() {
    mDirection = Direction::Right;
    mIsAlive = true;
    mGrowPending = false;
    mBody.clear();
    for (int i = 0; i < 3; ++i){
        sf::RectangleShape segment;
        segment.setSize(sf::Vector2f(GRID_SIZE - 1, GRID_SIZE - 1));
        segment.setFillColor(sf::Color::Green);
        segment.setPosition(WINDOW_WIDTH / 2 - i * GRID_SIZE, WINDOW_HEIGHT / 2);
        mBody.push_back(segment);
    }
}

void Snake::grow() {mGrowPending = true;}


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


sf::Vector2f Snake::getHeadPosition() const {
    if (mBody.empty()) {
        return sf::Vector2f(-1, -1);
    }
    return mBody.front().getPosition();
}

void Snake::update() {
    if (!mIsAlive || mDirection == Direction::None) return;

    sf::RectangleShape newHead = mBody.front();
    
    // switch case 的移動邏輯不變
    switch (mDirection) {
        case Direction::Up:    newHead.move(0, -GRID_SIZE); break;
        case Direction::Down:  newHead.move(0, GRID_SIZE);  break;
        case Direction::Left:  newHead.move(-GRID_SIZE, 0); break;
        case Direction::Right: newHead.move(GRID_SIZE, 0);  break;
        default: break;
    }
    
    // 邊界碰撞偵測不變
    sf::Vector2f headPos = newHead.getPosition();
    if (headPos.x < 0 || headPos.x >= WINDOW_WIDTH || headPos.y < 0 || headPos.y >= WINDOW_HEIGHT) {
        mIsAlive = false;
        return;
    }

    mBody.push_front(newHead);

    // 【修改】核心成長邏輯
    // 只有在「沒有」待成長指令時，才移除尾巴
    if (mGrowPending) {
        mGrowPending = false; // 成長指令已執行，重設標記為 false
    } else {
        mBody.pop_back(); // 如果沒有成長指令，就像平常一樣移除尾巴
    }
}


void Snake::render(sf::RenderWindow& window){
    for (const auto& segment : mBody){
        window.draw(segment);
    }
}
