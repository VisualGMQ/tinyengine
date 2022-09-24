#include "engine/components/sprite.hpp"

namespace engine {

void SpriteComponent::Reset() {
    Component::Reset();
    texture = nullptr;
    region.position.Set(0, 0);
    region.size.Set(0, 0);
    color.Set(1, 1, 1);
    size.Set(0, 0);
    flip = None;
    offset.Set(0, 0);
}

}