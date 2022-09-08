#pragma once

#include "engine/core/log.hpp"
#include "engine/core/scene.hpp"
#include "engine/core/configer.hpp"
#include "engine/input/input.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/shader.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/input/mouse.hpp"
#include "engine/ecs/component.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/ecs/world.hpp"
#include "engine/renderer/image.hpp"
#include "engine/core/timer.hpp"
#include "engine/renderer/tilesheet.hpp"
#include "engine/ui/ui_system.hpp"

enum {EASY, HARD};

class UIScene: public engine::Scene {
public:
    UIScene(const std::string& name): engine::Scene(name) {}

    void OnInit() override;
    void OnUpdate() override;
    void OnQuit() override;
};