#include "Bullet.h"
#include <cmath>

constexpr float PI = 3.14159265f;


/*
建構函式 Bullet(...):
    它接收 Player 的位置和角度。
    它設定子彈的形狀（一個黃色的小長方形）。
    最關鍵的一步：它使用 sin 和 cos 三角函式，將「角度」和「速度大小 (_speed)」轉換成一個二維的「速度向量 (_velocity)」。這決定了子彈的飛行方向。
update(dt):
    子彈的 update 邏輯非常簡單，它不像 Player 需要檢查鍵盤，也不像 Asteroid 需要旋轉。它只需要根據速度向量 _velocity 不斷向前飛。
    重要：我們加入了一個邊界檢查。當子彈飛出螢幕一定距離後，我們就呼叫 _isAlive = false; 將它標記為死亡。這是為之後的「自動清理」機制做的準備，可以防止無數飛出螢幕的子彈物件永遠佔用著記憶體。
draw(window):
    和其它 GameObject 一樣，它負責將自己的形狀繪製到傳入的視窗上。
 * */

// Bullet 的建構函式實作
Bullet::Bullet(sf::Vector2f position, float angle)
    // 步驟 1: 初始化父類別 GameObject
    : GameObject("Bullet", "A projectile")
{
    // 步驟 2: 設定子彈的外觀
    // 我們希望子彈是一個細長的小長方形
    _shape.setSize({10.f, 3.f});
    _shape.setOrigin({5.f, 1.5f}); // 將中心點設在長方形的幾何中心
    _shape.setFillColor(sf::Color::Yellow); // 讓子彈是黃色的，更醒目

    // 步驟 3: 設定子彈的初始物理狀態
    _position = position; // 將繼承來的 _position 設為傳入的發射位置
    _shape.setRotation(angle); // 同步形狀的角度

    // 根據傳入的角度，計算出子彈的飛行速度向量
    // 注意：SFML 的角度是順時針為正，而數學上的三角函式是逆時針為正，
    // 所以這裡的計算和 Player 前進的計算完全一樣。
    float angleRad = angle * PI / 180.f; // 將角度轉換為弧度
    _velocity.x = std::cos(angleRad) * _speed;
    _velocity.y = std::sin(angleRad) * _speed;
}


std::unique_ptr<GameObject> Bullet::update(sf::Time dt) {
    // 子彈的 update 非常單純：就是根據它的速度不斷更新位置
    _position += _velocity * dt.asSeconds();
    // 為了讓子彈在飛出螢幕後能被系統清理掉，我們要檢查它的存活狀態
    // 如果子彈的位置遠遠超出了螢幕邊界，我們就把它標記為「不存活」
    if (_position.x < -100.f || _position.x > 900.f || _position.y < -100.f || _position.y > 700.f) {
        _isAlive = false; // _isAlive 是從 GameObject 繼承來的
    }
    return nullptr;
}

// Bullet 的 draw 函式實作
void Bullet::draw(sf::RenderWindow& window) const {
    // 和之前一樣，為了保持 const 正確性，我們複製一份 shape 來設定位置和繪製
    sf::RectangleShape shapeToDraw = _shape;
    shapeToDraw.setPosition(_position);
    window.draw(shapeToDraw);
}
