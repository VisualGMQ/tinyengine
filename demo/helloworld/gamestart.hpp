#pragma once

#include "engine/engine.hpp"

class GameStart: public engine::Scene {
public:
    GameStart(const std::string& name): engine::Scene(name) {}
    void OnInit() override;

private:
    engine::Font* font_;

    void initUI();
    void loadResources();
    void initOtherNode();
};