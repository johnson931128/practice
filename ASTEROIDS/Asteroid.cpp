#include "Asteroid.h"
#include <random> // CS106L 推薦的現代 C++ 作法，比 C 語言的 rand() 更優秀
#include <cmath>  // 為了 sin/cos

// 為了避免魔法數字 (magic numbers)，我們定義一些常數
constexpr float PI = 3.14159265f;

// === 修正點在這裡 ===
// 我們將亂數引擎提升到檔案級別的靜態變數 (file-level static)
// 這樣一來，這個 .cpp 檔內的所有函式都可以共用同一個高品質的亂數產生器
static std::random_device rd;
static std::mt19937 gen(rd()); // Mersenne Twister 演算法，高品質的亂數引擎

// C++17 現代隨機數生成輔助函式
// 產生一個在 [min, max] 範圍內的隨機浮點數
float randomFloat(float min, float max) {
    // 現在這個函式直接使用上面宣告的 gen，不再需要自己宣告一次
    std::uniform_real_distribution<> dis(min, max);
    return static_cast<float>(dis(gen));
}

// Asteroid 的建構函式實作
Asteroid::Asteroid(sf::Vector2u windowSize)
    // 第一步：初始化父類別 GameObject 的部分
    : GameObject("Asteroid", 0.f) 
{
    // 第二步：初始化 Asteroid 自己的成員變數
    float radius = randomFloat(15.f, 45.f);
    _radius = radius;
    _rotationSpeed = randomFloat(-50.f, 50.f);

    // 設定外觀 (使用我們剛剛初始化的 radius)
    _shape.setPointCount(static_cast<size_t>(randomFloat(6, 10)));
    _shape.setRadius(radius);
    _shape.setOrigin(radius, radius); 
    _shape.setFillColor(sf::Color::Transparent);
    _shape.setOutlineColor(sf::Color::White);
    _shape.setOutlineThickness(2.f);

    // 決定隨機的初始位置 (在視窗邊界外)
    float offscreenBuffer = radius + 5.f; 
    // 現在這裡可以合法地使用 gen 了！
    int edge = std::uniform_int_distribution<>(0, 3)(gen); // 0=上, 1=右, 2=下, 3=左
    
    sf::Vector2f spawnPos;
    switch (edge) {
        case 0: // 上方
            spawnPos = { randomFloat(0, static_cast<float>(windowSize.x)), -offscreenBuffer };
            break;
        case 1: // 右方
            spawnPos = { static_cast<float>(windowSize.x) + offscreenBuffer, randomFloat(0, static_cast<float>(windowSize.y)) };
            break;
        case 2: // 下方
            spawnPos = { static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) + offscreenBuffer };
            break;
        case 3: // 左方
            spawnPos = { -offscreenBuffer, randomFloat(0, static_cast<float>(windowSize.y)) };
            break;
    }
    _position = spawnPos;

    // 決定隨機的速度 (方向和速率)
    float angle = randomFloat(0.f, 2.f * PI);
    float speed = randomFloat(50.f, 150.f);
    _velocity = { std::cos(angle) * speed, std::sin(angle) * speed };
}

// 【修正點】修改 update 函式的回傳型別和加上回傳值
std::unique_ptr<GameObject> Asteroid::update(sf::Time dt) {
    _position += _velocity * dt.asSeconds();
    _shape.rotate(_rotationSpeed * dt.asSeconds());

    float radius = _shape.getRadius();
    if (_position.x < -radius) _position.x = 800.f + radius;
    if (_position.x > 800.f + radius) _position.x = -radius;
    if (_position.y < -radius) _position.y = 600.f + radius;
    if (_position.y > 600.f + radius) _position.y = -radius;

    // 因為小行星在 update 時不會產生新的物件，所以我們回傳空指標
    return nullptr;
}

// Asteroid 的 draw 函式實作
void Asteroid::draw(sf::RenderWindow& window) const {
    sf::CircleShape shapeToDraw = _shape;
    shapeToDraw.setPosition(_position);
    shapeToDraw.setRotation(_shape.getRotation());
    window.draw(shapeToDraw);
}



float Asteroid::getCollisionRadius() const {
    return _shape.getRadius();
}
