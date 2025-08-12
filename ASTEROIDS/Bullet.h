#pragma once

#include "GameObject.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Bullet : public GameObject {
public:
    // 建構函式：
    // 一顆子彈被「創造」出來時，必須知道兩件事：
    // 1. 它的初始位置 (position)，也就是從哪裡發射。
    // 2. 它的飛行角度 (angle)，也就是要朝哪個方向飛。
    Bullet(sf::Vector2f position, float angle);

    // 履行與 GameObject 的合約，提供自己的 update 和 draw 實作。
    std::unique_ptr<GameObject> update(sf::Time dt) override;
    void draw(sf::RenderWindow& window) const override;


private:
    // 為了跟玩家的三角形和小行星的多邊形區分，我們用一個簡單的長方形來代表子彈。
    sf::RectangleShape _shape;

    // 子彈有固定的飛行速度。
    const float _speed = 800.f;
};
