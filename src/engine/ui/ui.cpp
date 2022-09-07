#include "engine/ui/ui.hpp"
#include "engine/core/context.hpp"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

namespace engine {

nk_glfw UI::glfw = {0};
nk_context* UI::ctx = nullptr;
nk_font_atlas* UI::atlas = nullptr;

void UI::Init() {
    ctx = nk_glfw3_init(&glfw, engine::Context::GetWindow(), NK_GLFW3_INSTALL_CALLBACKS);
    nk_font_atlas* atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    nk_font *font = nk_font_atlas_add_from_file(atlas, "C:/Windows/Fonts/simhei.ttf", 20, 0);
    nk_glfw3_font_stash_end(&glfw);
    nk_style_set_font(ctx, &font->handle);
}

void UI::Quit() {
    nk_glfw3_shutdown(&glfw);
}

void UI::Update() {
    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

void UI::NewFrame() {
    nk_glfw3_new_frame(&glfw);
}

}