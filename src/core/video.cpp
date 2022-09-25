#include "engine/core/video.hpp"

namespace engine {

SDL_Window* Video::window_ = nullptr;
bool Video::shouldClose_ = false;
Vec2 Video::initSize_;

void Video::Init(std::string_view title, int w, int h, bool resizable) {
    initSize_.Set(w, h);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Loge("SDL init failed: {}", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    uint32_t flags = SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI;
    if (resizable) {
        flags |= SDL_WINDOW_RESIZABLE;
    }
    window_ = SDL_CreateWindow(title.data(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              w, h,
                              flags);

    if (!window_) {
        SDL_Quit();
        Loge("window create failed");
        exit(2);
    }

    SDL_GL_CreateContext(window_);
    gladLoadGL();

    glViewport(0, 0, w, h);
    shouldClose_ = false;
}

void Video::Quit() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Video::SwapBuffers() {
    SDL_GL_SwapWindow(window_);
}

bool Video::ShouldClose() {
    return shouldClose_;
}

void Video::Close() {
    shouldClose_ = true;
}

}
