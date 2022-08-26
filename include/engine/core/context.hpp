#pragma once

#include "engine/core/pch.hpp"

namespace engine {

class Context final {
public:
    DLLEXPORT static void Init(const std::string& title, int w, int h);
    DLLEXPORT static void Quit();
    
    DLLEXPORT static void SwapBuffers();
    DLLEXPORT static bool ShouldClose();

private:
    static GLFWwindow* window_;
};

}