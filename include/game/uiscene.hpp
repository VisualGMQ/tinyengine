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

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear/nuklear.h"
#include "engine/ui/nuklear_glfw_gl3.hpp"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

enum {EASY, HARD};

class UIScene: public engine::Scene {
public:
    UIScene(const std::string& name): engine::Scene(name) {}

    void OnInit() override;
    void OnUpdate() override;
    void OnQuit() override;

private:
    nk_glfw glfw = {0};
    nk_context* ctx;
    nk_font_atlas *atlas;
    nk_colorf bg;
    int op = EASY;
    float value = 0.6f;
    int i =  20;
};