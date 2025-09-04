#include "RigidBody.h"

RigidBody::RigidBody(float mass, float restitution, Vector2D position)
    : mass(mass), 
      restitution(restitution), 
      position(position), 
      velocity(0.0f, 0.0f), 
      acceleration(0.0f, 0.0f) {}

void RigidBody::applyForce(const Vector2D& force) {
    if (mass > 0.0f) {
        // 牛頓第二運動定律: F = ma  =>  a = F/m
        acceleration = acceleration + force / mass;
    }
}
