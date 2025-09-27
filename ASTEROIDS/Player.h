#pragma once

#include "GameObject.h" // 我們只需要引入 GameObject.h
// #include <memory> 已經被 GameObject.h 引入，這裡可以省略

// 向前宣告 (Forward Declaration)
class Bullet;

class Player : public GameObject {
public:
    Player();

    // 現在這個 override 是合法的了，因為父類別的 update 也回傳 unique_ptr
    // 但請注意，回傳型別必須和父類別完全一樣，是 unique_ptr<GameObject>
    std::unique_ptr<GameObject> update(sf::Time dt) override;
    float getCollisionRadius() const override;
    void draw(sf::RenderWindow& window) const override;

private:
    sf::ConvexShape _shape;
    float _rotationSpeed;
    float _movementSpeed;
    bool _isMoving;
    
    // 【修正點】
    // 我們需要引入 SFML 的標頭檔，才能使用 sf::Time 和 sf::seconds
    sf::Time _fireCooldown;
    const sf::Time _fireInterval = sf::seconds(0.2f);
};
