#pragma once

#include "engine/ecs/component.hpp"
#include "engine/components/node.hpp"

namespace engine {

class RigidBodyComponent: public Component {
public:
    RigidBodyComponent(ComponentID id): Component(id) { Reset(); }
    void Reset() override;

    float mass;
    float damping;
    Vec2 velocity;
    Vec2 force;
    float maxSpeed;
};

class BoxColliderComponent: public Component {
public:
    friend class ColliderCollectSystem;

    BoxColliderComponent(ComponentID id): Component(id) { Reset(); }
    void Reset() override;

    float halfWidth;
    float halfHeight;
    Vec2 offset;
    uint32_t layer;

private:
    bool pushedInLayer_;
};

}
