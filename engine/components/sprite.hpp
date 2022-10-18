#pragma once

#include "engine/ecs/component.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/renderer/image.hpp"

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
    Image image;
    Color color;
    Color keycolor;
    Size size;
    Vec2 offset;
    uint32_t flip;
};

}
