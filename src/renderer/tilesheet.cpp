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

std::shared_ptr<Image> TileSheet::Get(int col, int row) {
    return std::make_shared<Image>(texture_, Rect(col * tileWidth_, (row_ - row) * tileHeight_, tileWidth_, tileHeight_));
}

}