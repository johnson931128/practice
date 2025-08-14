#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class GameObject {
public:
    // 【修改點】建構函式需要額外接收 type 和 radius
    GameObject(const std::string& type, float radius)
        : _type(type), _isAlive(true), _radius(radius) {}

    virtual ~GameObject() = default;
    virtual std::unique_ptr<GameObject> update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    // 新的合約：所有遊戲物件都必須能回報自己的碰撞半徑。
    // 這是一個純虛擬函式，代表 GameObject 本身沒有實作，
    // 強制所有繼承它的子類別都必須提供自己的版本。
    virtual float getCollisionRadius() const = 0;

    // --- Getter 函式 ---
    const std::string& getType() const { return _type; } // <--- 新增
    sf::Vector2f getPosition() const { return _position; }
    float getRadius() const { return _radius; }         // <--- 新增
    bool isAlive() const { return _isAlive; }
    
    // --- Setter 函式 ---
    void destroy() { _isAlive = false; }

protected:
    // 我們不再需要 _name 和 _description，改用更實用的變數
    std::string _type;      // <--- 新增: 用來識別物件類型 (e.g., "Player", "Asteroid")
    bool _isAlive;
    float _radius;        // <--- 新增: 用於碰撞偵測的半徑
    sf::Vector2f _position;
    sf::Vector2f _velocity;
};
