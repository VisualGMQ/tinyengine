#pragma once

#include "engine/ecs/system.hpp"

namespace engine {

class World;

class PhysicsSystem: public System {
public:
    PhysicsSystem(engine::World* world): System(world) {}
    void Update(Entity*) override;
};

class CollideSystem: public System {
public:
    CollideSystem(engine::World* world): System(world) {}
    void Update(Entity*) override;
};

}