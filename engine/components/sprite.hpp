#pragma once

#include "engine/ecs/component.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/renderer/tilesheet.hpp"

namespace engine {

enum Flip {
    None = 0x00,
    Vertical = 0x01,
    Horizontal = 0x02,
    Both = Vertical | Horizontal,
};

struct ImageInfo final {
public:
    Texture* texture;
    Rect region;

    ImageInfo(): texture(nullptr) {}
    explicit ImageInfo(const TileSheet::Tile& tile) {
        *this = tile;
    }

    ImageInfo& operator=(const TileSheet::Tile& tile) {
        texture = tile.texture;
        region = tile.region;
        return *this;
    }
};

class SpriteComponent: public Component {
public:
    SpriteComponent(ComponentID id): Component(id) { Reset(); }

    void Reset();
    ImageInfo image;
    Color color;
    Color keycolor;
    Size size;
    Vec2 offset;
    uint32_t flip;
};

}
