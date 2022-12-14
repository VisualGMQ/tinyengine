#pragma once

#include "engine/ecs/system.hpp"
#include "engine/physics/physics.hpp"
#include "engine/core/timer.hpp"

namespace engine {

constexpr float DefaultMaxSpeed = 100;

class World;

class PhysicsSystem: public EntityUpdateSystem {
public:
    PhysicsSystem(engine::World* world): EntityUpdateSystem(world) {}
    void Update(Entity*) override;

    void ChangeMaxSpeed(float maxSpeed) { maxSpeed_ = maxSpeed; }

private:
    float maxSpeed_ = DefaultMaxSpeed;
};

class CollideSystem: public PerFrameSystem {
public:
    CollideSystem(engine::World* world): PerFrameSystem(world) {}
    void Update() override;

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);

private:
    bool isCollide(BoxColliderComponent* box1, const Vec2& pos1, BoxColliderComponent* box2, const Vec2& pos2);
    void doCollideIter(BoxColliderComponent* box1, BoxColliderComponent* box2,
                       RigidBodyComponent* rigid1, RigidBodyComponent* rigid2,
                       Node2DComponent* node1, Node2DComponent* node2);

    std::vector<Entity*> entities_;
};

class ColliderCollectSystem: public EntityUpdateSystem {
public:
    ColliderCollectSystem(engine::World* world, CollideSystem* collidSystem): EntityUpdateSystem(world), collideSystem_(collidSystem) {}
    void Update(Entity* entity) override;

private:
    CollideSystem* collideSystem_;
};

}