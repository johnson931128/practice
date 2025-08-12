#include "Player.h"
#include "Bullet.h"
#include <cmath>

Player::Player() 
    : GameObject("Player", "Player's spaceship"),
      _rotationSpeed(200.f), 
      _movementSpeed(300.f), 
      _isMoving(false),
      _fireCooldown(sf::Time::Zero)
{
    _shape.setPointCount(3);
    _shape.setPoint(0, {20.f, 0.f});
    _shape.setPoint(1, {-10.f, -10.f});
    _shape.setPoint(2, {-10.f, 10.f});
    _shape.setFillColor(sf::Color::White);
    _shape.setOrigin(5.f, 0.f);
    _position = {400.f, 300.f};
}

// 【修正點】回傳型別改為 std::unique_ptr<GameObject>
std::unique_ptr<GameObject> Player::update(sf::Time dt) {
    // 1. 旋轉
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        _shape.rotate(-_rotationSpeed * dt.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _shape.rotate(_rotationSpeed * dt.asSeconds());
    }

    // 2. 前進
    _isMoving = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    if (_isMoving) {
        float angle = _shape.getRotation() * 3.14159f / 180.f;
        _velocity = {std::cos(angle) * _movementSpeed, std::sin(angle) * _movementSpeed};
    } else {
        _velocity = {0.f, 0.f};
    }
    _position += _velocity * dt.asSeconds();

    // 3. 邊界環繞
    if (_position.x < 0) _position.x = 800;
    if (_position.x > 800) _position.x = 0;
    if (_position.y < 0) _position.y = 600;
    if (_position.y > 600) _position.y = 0;

    // 4. 開火
    if (_fireCooldown > sf::Time::Zero) {
        _fireCooldown -= dt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _fireCooldown <= sf::Time::Zero) {
        _fireCooldown = _fireInterval;
        // 我們建立的是 Bullet，但因為 Bullet 是 GameObject 的子類，
        // 所以可以被裝在 unique_ptr<GameObject> 中回傳。
        return std::make_unique<Bullet>(_position, _shape.getRotation());
    }
    
    // 沒開火就回傳空指標
    return nullptr;
}

// 修正 Player.cpp 中的 draw 函式，補上漏掉的 setRotation
void Player::draw(sf::RenderWindow& window) const {
    sf::ConvexShape shapeToDraw = _shape;
    shapeToDraw.setPosition(_position);
    shapeToDraw.setRotation(_shape.getRotation()); // 確保旋轉角度也能被正確繪製
    window.draw(shapeToDraw);
}
