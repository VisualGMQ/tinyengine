#pragma once

#include "engine/engine.hpp"

class Draw2DBehavior final: public engine::Behavior {
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnQuit() override;

private:
    engine::Font* font_;
};