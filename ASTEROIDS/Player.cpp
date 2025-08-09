#include "Player.h"
#include <cmath> // 為了 sin 和 cos

Player::Player() 
    : GameObject("Player", "Player's spaceship"), mRotationSpeed(200.f), mMovementSpeed(300.f), mIsMoving(false) {
    
    // 設定太空船的形狀為一個三角形
    mShape.setPointCount(3);
    mShape.setPoint(0, sf::Vector2f(20, 0));
    mShape.setPoint(1, sf::Vector2f(-10, -10));
    mShape.setPoint(2, sf::Vector2f(-10, 10));
    mShape.setFillColor(sf::Color::White);
    mShape.setOrigin(5, 0); // 將旋轉中心設在三角形的重心附近

    // 設定初始位置
    mPosition = sf::Vector2f(400, 300); // 畫面中央
}

void Player::update(sf::Time dt) {
    // 1. 處理旋轉
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        mShape.rotate(-mRotationSpeed * dt.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        mShape.rotate(mRotationSpeed * dt.asSeconds());
    }

    // 2. 處理前進
    mIsMoving = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    
    if (mIsMoving) {
        float angle = mShape.getRotation() * 3.14159f / 180.f; // 角度轉弧度
        mVelocity = sf::Vector2f(std::cos(angle) * mMovementSpeed, std::sin(angle) * mMovementSpeed);
    } else {
        mVelocity = sf::Vector2f(0, 0);
    }

    // 3. 更新位置
    mPosition += mVelocity * dt.asSeconds();

    // TODO: 處理螢幕邊界環繞 (wrap-around)
}

void Player::draw(sf::RenderWindow& window) const {
    // 在繪製前，先將物件的形狀同步到它目前的位置
    sf::ConvexShape shapeToDraw = mShape;
    shapeToDraw.setPosition(mPosition);
    window.draw(shapeToDraw);
}
