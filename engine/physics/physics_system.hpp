#pragma once

#include "engine/ecs/system.hpp"
#include "engine/physics/physics.hpp"
#include "engine/core/timer.hpp"

namespace engine {

class World;

class PhysicsSystem: public EntityUpdateSystem {
public:
    PhysicsSystem(engine::World* world): EntityUpdateSystem(world) {}
    void Update(Entity*) override;

    void ChangeMaxSpeed(float maxSpeed) { maxSpeed_ = maxSpeed; }

private:
    float maxSpeed_ = 100;
};

class CollideSystem: public PerFrameSystem {
public:
    CollideSystem(engine::World* world): PerFrameSystem(world) {}
    void Update() override;

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);

private:
    bool isCollide(BoxColliderComponent* box1, const Vec2& pos1, BoxColliderComponent* box2, const Vec2& pos2);

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