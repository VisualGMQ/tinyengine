#pragma once

#include "engine/ecs/component.hpp"

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

namespace engine {

class UI final {
public:
    static void Init();
    static void Quit();
    static void Update();
    static void NewFrame();
    static nk_glfw& GlfwContext() { return glfw; }
    static nk_context* NkContext() { return ctx; }

private:
    static nk_glfw glfw;
    static nk_context* ctx;
    static nk_font_atlas *atlas;
};

}
