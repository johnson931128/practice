#ifndef VECTOR2D_H
#define VECTOR2D_H

// 這是一個簡單的 2D 向量結構，用來表示位置、速度、加速度等。
// 使用 struct 是因為它的成員預設是 public，對於這樣一個純數據容器來說很方便。
struct Vector2D {
    float x, y;

    // 預設建構子
    Vector2D();
    // 參數化建構子
    Vector2D(float x, float y);

    // 實用的向量函式
    float magnitude() const;
    void normalize();
};

// 非成員函式的運算子重載 (更具彈性)
Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
Vector2D operator*(const Vector2D& v, float scalar);
Vector2D operator*(float scalar, const Vector2D& v);
Vector2D operator/(const Vector2D& v, float scalar);

#endif // VECTOR2D_H
