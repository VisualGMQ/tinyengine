#pragma once

#include "engine/core/pch.hpp"

namespace engine {

class DLLEXPORT Context final {
public:
    Context() = delete;

    static void Init(const std::string& title, int w, int h, bool resizable);
    static void Quit();
    
    static void SwapBuffers();
    static bool ShouldClose();
    static void Close();

    static SDL_Window* GetWindow();
    static Vec2 GetWindowSize() {
        int w, h;
        SDL_GetWindowSize(window_, &w, &h);
        return Vec2(w, h);
    }
    static const Vec2& GetInitSize() { return initSize_; }

private:
    static SDL_Window* window_;
    static bool shouldClose_;
    static Vec2 initSize_;
};

}
