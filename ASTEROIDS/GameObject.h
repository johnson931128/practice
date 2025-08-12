#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory> // <--- 新增：為了使用 std::unique_ptr

class GameObject {
public:
    GameObject(const std::string& name, const std::string& description)
        : _name(name), _description(description), _isAlive(true) {}

    virtual ~GameObject() = default;

    // === 核心修正 ===
    // 我們修改合約，讓 update 函式可以回傳一個指向新 GameObject 的指標。
    // 如果沒有要產生物件，它就回傳 nullptr。
    // 注意：回傳型別是泛型的 GameObject，而不是特定的 Bullet。
    virtual std::unique_ptr<GameObject> update(sf::Time dt) = 0;
    
    virtual void draw(sf::RenderWindow& window) const = 0;

    // Getter / Setter
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
