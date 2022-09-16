#pragma once

#include "engine/ecs/component.hpp"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_sdl_gl3.h"

namespace engine {

class UI final {
public:
    DLLEXPORT static void Init();
    DLLEXPORT static void Quit();
    static void Update();
    static nk_context* NkContext() { return ctx_; }
    static void HandleEvent(SDL_Event*);
    static void InputBegin();
    static void InputEnd();

private:
    static nk_context* ctx_;
    static nk_font_atlas *atlas_;
};

}
