#include "engine/renderer/tilesheet.hpp"

namespace engine {

TileSheet::TileSheet(TileSheetID id, const std::string& name, Texture* texture, int col, int row)
    : id_(id),
      name_(name),
      texture_(texture),
      col_(col), row_(row),
      tileWidth_(texture_->Width() / col), tileHeight_(texture_->Height() / row) {
}

TileSheet::Tile TileSheet::Get(int col, int row) {
    Tile tile;
    tile.texture = texture_;
    tile.region = Rect(col * tileWidth_, row * tileHeight_, tileWidth_, tileHeight_);
    return tile;
}

TileSheetID TileSheetFactory::curId_ = 0; 
std::unordered_map<TileSheetID, std::unique_ptr<TileSheet>> TileSheetFactory::datas_;


TileSheet* TileSheetFactory::Create(const std::string& name, Texture* texture, int col, int row) {
    if (auto tilesheet = Find(name); tilesheet) {
        Logw("tilesheet {} already exists", tilesheet->Name());
        return tilesheet;
    }

    TileSheetID id = curId_++;
    auto tilesheet = std::make_unique<TileSheet>(id, name, texture, col, row);
    auto result = tilesheet.get();
    datas_[id] = std::move(tilesheet);
    return result;
}

TileSheet* TileSheetFactory::Find(const std::string& name) {
    for (auto& [key, value] : datas_) {
        if (value->Name() == name) {
            return value.get();
        }
    }
    return nullptr;
}

TileSheet* TileSheetFactory::Find(TileSheetID id) {
    auto it = datas_.find(id);
    if (it != datas_.end()) {
        return it->second.get();
    }
    return nullptr;
}

}