#include "engine/input/mouse.hpp"

namespace engine {

void Mouse::Hide() {
    glfwSetInputMode(Context::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Mouse::Show() {
    glfwSetInputMode(Context::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Mouse::IsShowing() {
    auto mode = glfwGetInputMode(Context::GetWindow(), GLFW_CURSOR);
    return mode != GLFW_CURSOR_DISABLED && mode != GLFW_CURSOR_HIDDEN;
}

}