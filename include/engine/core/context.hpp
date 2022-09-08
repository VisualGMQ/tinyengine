#pragma once

#include "engine/core/pch.hpp"

namespace engine {

class DLLEXPORT Context final {
public:
    Context() = delete;

    static void Init(const std::string& title, int w, int h);
    static void Quit();
    
    static void SwapBuffers();
    static bool ShouldClose();
    static void Close();

    static GLFWwindow* GetWindow();

private:
    static GLFWwindow* window_;
};

}
