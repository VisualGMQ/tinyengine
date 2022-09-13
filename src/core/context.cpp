#include "engine/core/context.hpp"

namespace engine {

SDL_Window* Context::window_ = nullptr;
bool Context::shouldClose_ = false;
Vec2 Context::initSize_;

SDL_Window* Context::GetWindow() {
    return window_;
}

void Context::Init(const std::string& title, int w, int h, bool resizable) {
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
    window_ = SDL_CreateWindow(title.c_str(),
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

void Context::Quit() {
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Context::SwapBuffers() {
    SDL_GL_SwapWindow(window_);
}

bool Context::ShouldClose() {
    return shouldClose_;
}

void Context::Close() {
    shouldClose_ = true;
}

}
