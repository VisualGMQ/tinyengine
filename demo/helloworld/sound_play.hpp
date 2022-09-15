#pragma once

#include "engine/engine.hpp"

class SoundBehavior: public engine::Behavior {
public:
    void OnInit() override;
    void OnUpdate() override;
    void OnQuit() override;

private:
    engine::Sound* sound1_;
    engine::Sound* sound2_;
};