#include "Food.h"
#include <random> // 引用 C++ 的隨機數函式庫
#include "Config.h"

Food::Food() {
    // 設定食物方塊的大小和顏色
    mShape.setSize(sf::Vector2f(GRID_SIZE - 1, GRID_SIZE - 1));
    mShape.setFillColor(sf::Color::Red);
    // 第一次被創造時，就呼叫 respawn() 來決定它的初始位置
    respawn();
}

sf::Vector2f Food::getPosition() const {
    return mShape.getPosition();
}

void Food::respawn() {
    // 使用 C++11 的 <random> 函式庫來產生高品質的隨機數
    std::random_device rd; // 取得一個真正的隨機種子
    std::mt19937 engine(rd()); // 使用 Mersenne Twister 演算法作為亂數引擎

    // 設定 x 座標的隨機範圍 (從第 0 格到最後一格)
    std::uniform_int_distribution<> distX(0, static_cast<int>(WINDOW_WIDTH / GRID_SIZE) - 1);
    // 設定 y 座標的隨機範圍
    std::uniform_int_distribution<> distY(0, static_cast<int>(WINDOW_HEIGHT / GRID_SIZE) - 1);

    // 產生隨機的格線座標，並轉換成像素座標
    mShape.setPosition(distX(engine) * GRID_SIZE, distY(engine) * GRID_SIZE);
}

void Food::render(sf::RenderWindow& window) {
    window.draw(mShape);
}
