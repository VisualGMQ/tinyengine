#pragma once

#include "engine/ecs/component.hpp"
#include "engine/renderer/texture.hpp"

namespace engine {

enum Flip {
    None = 0x00,
    Vertical = 0x01,
    Horizontal = 0x02,
    Both = Vertical | Horizontal,
};

class SpriteComponent: public Component {
public:
    SpriteComponent(ComponentID id): Component(id) { Reset(); }

    void Reset();

    Texture* texture;
    Rect region;
    Color color;
    Size size;
    Vec2 offset;
    uint32_t flip;
};

}