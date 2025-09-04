#include "Vector2D.h"
#include <cmath> // 需要使用 sqrtf

Vector2D::Vector2D() : x(0.0f), y(0.0f) {}

Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

float Vector2D::magnitude() const {
    return sqrtf(x * x + y * y);
}

void Vector2D::normalize() {
    float mag = magnitude();
    if (mag > 0.0f) {
        x /= mag;
        y /= mag;
    }
}

Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.x + v2.x, v1.y + v2.y);
}

Vector2D operator-(const Vector2D& v1, const Vector2D& v2) {
    return Vector2D(v1.x - v2.x, v1.y - v2.y);
}

Vector2D operator*(const Vector2D& v, float scalar) {
    return Vector2D(v.x * scalar, v.y * scalar);
}

// 為了讓 `2.0f * vec` 這種寫法也能運作
Vector2D operator*(float scalar, const Vector2D& v) {
    return Vector2D(v.x * scalar, v.y * scalar);
}

Vector2D operator/(const Vector2D& v, float scalar) {
    return Vector2D(v.x / scalar, v.y / scalar);
}
