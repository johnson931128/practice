#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(Vector2D gravity) : m_gravity(gravity) {}

void PhysicsWorld::addBody(std::unique_ptr<RigidBody> body) {
    // 使用 std::move 將 body 的所有權轉移給 vector
    m_bodies.push_back(std::move(body));
}

void PhysicsWorld::update(float dt) {
    // 遍歷世界中的每一個物體
    for (auto& body : m_bodies) {
        // 1. 施加重力
        body->applyForce(m_gravity * body->mass);

        // 2. 積分 (更新速度和位置) - 歐拉積分
        body->velocity = body->velocity + body->acceleration * dt;
        body->position = body->position + body->velocity * dt;

        // 3. 清除這一幀的力，為下一幀做準備
        body->acceleration = Vector2D(0.0f, 0.0f);
    }
}

const std::vector<std::unique_ptr<RigidBody>>& PhysicsWorld::getBodies() const {
    return m_bodies;
}
