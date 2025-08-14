#pragma once

#include "GameObject.h"
#include <SFML/Graphics/CircleShape.hpp>

class Asteroid : public GameObject {
public:
    // 這是一個「建構函式」，用來建立一顆新的小行星。
    // 它需要知道遊戲視窗的大小 (windowSize)，以便決定小行星該從哪個螢幕邊界外生成。
    Asteroid(sf::Vector2u windowSize);

    // 我們必須「覆寫」(override) 來自 GameObject 的這兩個函式。
    // 這是繼承時的「合約」，要求我們必須提供 Asteroid 自己版本的更新邏輯和繪製方式。
    std::unique_ptr<GameObject> update(sf::Time dt) override;
    void draw(sf::RenderWindow& window) const override;
    float getCollisionRadius() const override;
private:
    // 我們選用 SFML 函式庫中的 CircleShape 來代表小行星的形狀。
    sf::CircleShape _shape;
    
    // 這個變數用來記錄每顆小行星自己獨特的旋轉速度。
    float _rotationSpeed;
};
