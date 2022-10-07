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
};

class BoxColliderComponent: public Component {
public:
    BoxColliderComponent(ComponentID id): Component(id) { Reset(); }
    void Reset() override;

private:
    float halfWidth;
    float halfHeight;
    Vec2 offset;
};

}
