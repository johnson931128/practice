#ifndef PHYSICSWORLD_H
#define PHYSICSWORLD_H

#include <vector>
#include <memory> // 為了 std::unique_ptr
#include "RigidBody.h"

class PhysicsWorld {
public:
    PhysicsWorld(Vector2D gravity);

    // 新增一個物體到世界中
    void addBody(std::unique_ptr<RigidBody> body);

    // 更新世界中的所有物體
    void update(float dt);

    // 提供一個 const 的方式來獲取物體列表 (未來給渲染器使用)
    const std::vector<std::unique_ptr<RigidBody>>& getBodies() const;

private:
    Vector2D m_gravity;
    std::vector<std::unique_ptr<RigidBody>> m_bodies;
};

#endif // PHYSICSWORLD_H
