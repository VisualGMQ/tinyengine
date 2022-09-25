#include "engine/components/sprite.hpp"

namespace engine {

void SpriteComponent::Reset() {
    Component::Reset();
    image.texture = nullptr;
    image.region.position.Set(0, 0);
    image.region.size.Set(0, 0);
    color.Set(1, 1, 1);
    keycolor.Set(1, 1, 1);
    size.Set(0, 0);
    flip = None;
    offset.Set(0, 0);
}

}
