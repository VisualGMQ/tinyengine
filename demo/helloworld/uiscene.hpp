#pragma once
#include "engine/engine.hpp"

enum {EASY, HARD};

class UIScene: public engine::Scene {
public:
    UIScene(const std::string& name): engine::Scene(name) {}

    void OnInit() override;
    void OnUpdate() override;
    void OnQuit() override;
};