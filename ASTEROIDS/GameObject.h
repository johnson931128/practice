#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameObject {
public:
    // 【修正點】加入了這個必要的建構函式
    // 子類別在建立時，必須呼叫這個建構函式來初始化基礎部分
    GameObject(const std::string& name, const std::string& description)
        : _name(name), _description(description), _isAlive(true) {}

    // 虛擬解構函式
    virtual ~GameObject() = default;

    // 純虛擬函式
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    // 公開的 getter / setter
    sf::Vector2f getPosition() const { return _position; }
    bool isAlive() const { return _isAlive; }
    void destroy() { _isAlive = false; }

protected:
    std::string _name;
    std::string _description;
    sf::Vector2f _position;
    sf::Vector2f _velocity;
    bool _isAlive;
};
