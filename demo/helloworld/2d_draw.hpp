#pragma once

#include "engine/engine.hpp"

class Draw2DBehavior final: public engine::Behavior {
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnQuit() override;

private:
    std::shared_ptr<engine::Image> cppImage_;
    std::unique_ptr<engine::TileSheet> tilesheet_;
    std::shared_ptr<engine::Image> tile1_;
    std::shared_ptr<engine::Image> tile2_;
    std::shared_ptr<engine::Image> tile3_;
    engine::Font* font_;
};