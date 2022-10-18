#pragma once

#include "engine/physics/physics.hpp"
#include "engine/ecs/system.hpp"
#include "engine/ecs/world.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/renderer/renderer.hpp"

namespace engine::debug {

class ColliderOutlineSystem: public EntityUpdateSystem {
public:
    ColliderOutlineSystem(engine::World* world): EntityUpdateSystem(world) {}

    void Update(Entity*);
};

}