#include "engine/physics/physics.hpp"

namespace engine {

void RigidBodyComponent::Reset() {
    mass = 1;
    damping = 0;
}

void BoxColliderComponent::Reset() {
    halfWidth = 16;
    halfHeight = 16;
    offset.Set(0, 0);
}

}
