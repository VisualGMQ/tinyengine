#pragma once

#include "engine/renderer/renderer.hpp"
#include "engine/renderer/image.hpp"
#include "engine/renderer/texture.hpp"

namespace engine {

class DLLEXPORT TileSheet final {
public:
    TileSheet(const std::string& name, int col, int row);
    TileSheet(TextureID id, int col, int row);

    std::shared_ptr<Image> Get(int col, int row);

private:
    Texture* texture_; 
    int row_, col_;
    int tileWidth_, tileHeight_;
};

}