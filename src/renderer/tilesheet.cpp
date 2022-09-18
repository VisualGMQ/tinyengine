#include "engine/renderer/tilesheet.hpp"

namespace engine {

TileSheet::TileSheet(const std::string& name, int col, int row)
    : texture_(TextureFactory::Find(name)),
      col_(col), row_(row),
      tileWidth_(texture_->Width() / col), tileHeight_(texture_->Height() / row) {
}

TileSheet::TileSheet(TextureID id, int col, int row)
     : texture_(TextureFactory::Find(id)), col_(col), row_(row),
       tileWidth_(texture_->Width() / col), tileHeight_(texture_->Height() / row) {
}

TileSheet::Tile TileSheet::Get(int col, int row) {
    Tile tile;
    tile.texture = texture_;
    tile.region = Rect(col * tileWidth_, (row_ - row - 1) * tileHeight_, tileWidth_, tileHeight_);
    return tile;
}

}