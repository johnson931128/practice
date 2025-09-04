#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

struct RigidBody {
    // 物理屬性
    float mass;
    float restitution; // 恢復係數 (0-1, 1代表完全彈性)

    // 狀態屬性
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;

    // 建構子
    RigidBody(float mass, float restitution, Vector2D position);

    // 施加一個力
    void applyForce(const Vector2D& force);
};

#endif // RIGIDBODY_H
