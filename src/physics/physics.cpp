#include "engine/physics/physics.hpp"
#include "engine/ecs/world.hpp"
#include "engine/physics/physics_system.hpp"

namespace engine {

void RigidBodyComponent::Reset() {
    mass = 1;
    damping = 0;
    velocity.Set(0, 0);
    force.Set(0, 0);
    maxSpeed = DefaultMaxSpeed;

    Component::Reset();
}

void BoxColliderComponent::Reset() {
    halfWidth = 16;
    halfHeight = 16;
    offset.Set(0, 0);
    layer = 0x01;
    pushedInLayer_ = false;

    auto& systems = World::Instance()->PerFrameSystems();
    for (auto& system : systems) {
        CollideSystem* collidSystem = dynamic_cast<CollideSystem*>(system.get());
        if (collidSystem) {
            collidSystem->RemoveEntity(Parent());
        }
    }

    Component::Reset();
}

}
