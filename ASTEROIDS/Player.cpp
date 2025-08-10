#include "Player.h"
#include <cmath> // 為了 sin 和 cos

// 【修正點】在初始化列表中，我們必須先呼叫基礎類別的建構函式
Player::Player() 
    : GameObject("Player", "Player's spaceship"), // 告訴 C++ 如何建立 GameObject 的部分
      _rotationSpeed(200.f), 
      _movementSpeed(300.f), 
      _isMoving(false) 
{
    // 設定太空船的形狀為一個三角形
    _shape.setPointCount(3);
    _shape.setPoint(0, sf::Vector2f(20, 0));
    _shape.setPoint(1, sf::Vector2f(-10, -10));
    _shape.setPoint(2, sf::Vector2f(-10, 10));
    _shape.setFillColor(sf::Color::White);
    _shape.setOrigin(5, 0); // 將旋轉中心設在三角形的重心附近

    // 設定初始位置 (繼承自 GameObject 的成員)
    _position = sf::Vector2f(400, 300); // 畫面中央
}

void Player::update(sf::Time dt) {
    // 1. 處理旋轉
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _shape.rotate(-_rotationSpeed * dt.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _shape.rotate(_rotationSpeed * dt.asSeconds());
    }

    // 2. 處理前進
    _isMoving = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    
    if (_isMoving) {
        float angle = _shape.getRotation() * 3.14159f / 180.f; // 角度轉弧度
        _velocity = sf::Vector2f(std::cos(angle) * _movementSpeed, std::sin(angle) * _movementSpeed);
    } else {
        _velocity = sf::Vector2f(0, 0);
    }

    // 3. 更新位置 (繼承自 GameObject 的成員)
    _position += _velocity * dt.asSeconds();

    // TODO: 處理螢幕邊界環繞
}

void Player::draw(sf::RenderWindow& window) const {
    // 在繪製前，先將物件的形狀同步到它目前的位置
    sf::ConvexShape shapeToDraw = _shape;
    shapeToDraw.setPosition(_position);
    window.draw(shapeToDraw);
}
