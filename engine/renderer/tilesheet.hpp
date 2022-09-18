#pragma once

#include "engine/renderer/renderer.hpp"
#include "engine/renderer/image.hpp"
#include "engine/renderer/texture.hpp"

namespace engine {

class DLLEXPORT TileSheet final {
public:
    struct Tile {
        Texture* texture;
        Rect region;
    };

    TileSheet(const std::string& name, int col, int row);
    TileSheet(TextureID id, int col, int row);

    Tile Get(int col, int row);

private:
    Texture* texture_; 
    int row_, col_;
    int tileWidth_, tileHeight_;
};

}