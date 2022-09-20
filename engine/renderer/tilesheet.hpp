#pragma once

#include "engine/renderer/renderer.hpp"
#include "engine/renderer/image.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/core/log.hpp"

namespace engine {

using TileSheetID = uint32_t;

class DLLEXPORT TileSheet final {
public:
    struct Tile {
        Texture* texture;
        Rect region;
    };

    TileSheet(TileSheetID id, const std::string& name, Texture*, int col, int row);

    Tile Get(int col, int row);
    TileSheetID ID() const { return id_; }
    const std::string& Name() const { return name_; }
    Size TileSize() const { return Size(tileWidth_, tileHeight_); }

private:
    Texture* texture_; 
    int row_, col_;
    int tileWidth_, tileHeight_;
    std::string name_;
    TileSheetID id_;
};

class TileSheetFactory final {
public:
    TileSheetFactory() = delete;
    TileSheetFactory(const TileSheetFactory&) = delete;

    static TileSheet* Create(const std::string& name, Texture* texture, int col, int row);
    static TileSheet* Find(const std::string& name);
    static TileSheet* Find(TileSheetID);

private:
    static TileSheetID curId_; 
    static std::unordered_map<TileSheetID, std::unique_ptr<TileSheet>> datas_;
};

}