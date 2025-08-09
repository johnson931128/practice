#pragma once

#include "GameObject.h"

// Player 類別公開繼承自 GameObject
class Player : public GameObject {
public:
    // 建構函式
    Player();

    // 實作來自 GameObject 的純虛擬函式
    // override 關鍵字可以讓編譯器幫我們檢查是否真的覆寫了基礎類別的函式
    void update(sf::Time dt) override;
    void draw(sf::RenderWindow& window) const override;

private:
    sf::ConvexShape mShape; // 我們用凸多邊形來畫三角形太空船
    float mRotationSpeed;
    float mMovementSpeed;
    bool mIsMoving;
};
