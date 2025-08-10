#pragma once

#include "GameObject.h"

class Player : public GameObject {
public:
    // 建構函式
    Player();

    // 覆寫來自 GameObject 的純虛擬函式
    void update(sf::Time dt) override;
    void draw(sf::RenderWindow& window) const override;

private:
    sf::ConvexShape _shape; // 建議成員變數使用一致的前綴，例如 _
    float _rotationSpeed;
    float _movementSpeed;
    bool _isMoving;
};
