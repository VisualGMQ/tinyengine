#include "engine/ui/ui.hpp"
#include "engine/core/video.hpp"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

namespace engine {

nk_context* UI::ctx_ = nullptr;
nk_font_atlas* UI::atlas_ = nullptr;

void UI::Init() {
    ctx_ = nk_sdl_init((SDL_Window*)Video::GetWindow());
    struct nk_font_config config = nk_font_config(20);
    config.oversample_h = 1;
    config.oversample_v = 1;
    config.range = nk_font_chinese_glyph_ranges();
    nk_font_atlas* atlas;
    nk_sdl_font_stash_begin(&atlas);
    nk_font *font = nk_font_atlas_add_from_file(atlas, "C:/Windows/Fonts/simhei.ttf", 20, &config);
    nk_sdl_font_stash_end();
    nk_style_set_font(ctx_, &font->handle);
}

void UI::Quit() {
    nk_sdl_shutdown();
}

void UI::Update() {
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
}

void UI::InputBegin() {
    nk_input_begin(ctx_);
}

void UI::InputEnd() {
    nk_input_end(ctx_);
}

void UI::HandleEvent(SDL_Event* event) {
    nk_sdl_handle_event(event);
}

}