#pragma once

#include "engine/engine.hpp"

class TestScene: public engine::Scene {
public:
    TestScene(const std::string& name): engine::Scene(name) {}
    void OnInit() override;
    void OnQuit() override;
};