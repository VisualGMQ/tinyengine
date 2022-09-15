#pragma once

#include "engine/engine.hpp"

class Draw3DBehavior: public engine::Behavior {
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnQuit() override;

    bool OnMouseButtonDown(const SDL_MouseButtonEvent&) override {
        Loge("clicked");
        return true;
    }

private:
    std::shared_ptr<engine::Mesh> cube_;
    float lineRotationY_;
    engine::Vec2 rotation_;
};