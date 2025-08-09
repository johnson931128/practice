#pragma once
#include <SFML/Graphics.hpp>

// 這是我們遊戲世界中所有物件的抽象基礎類別
class GameObject {
public:
    // 虛擬解構函式，對於要被繼承的基礎類別來說至關重要
    virtual ~GameObject() = default;

    // 純虛擬函式 (Pure Virtual Functions)
    // 這兩個函式強制所有子類別都必須提供自己的實作版本
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    // 公開的 getter / setter 函式
    sf::Vector2f getPosition() const { return mPosition; }
    bool isAlive() const { return mIsAlive; }
    void destroy() { mIsAlive = false; } // 用於標記物件為「待銷毀」

protected:
    // protected 成員變數，讓子類別可以直接存取
    sf::Vector2f mPosition;
    sf::Vector2f mVelocity;
    bool mIsAlive{true}; // 使用 C++11 的成員初始化
};
