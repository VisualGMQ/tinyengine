#include "engine/core/context.hpp"

namespace engine {

GLFWwindow* Context::window_ = nullptr;

void Context::Init(const std::string& title, int w, int h) {
    if (!glfwInit()) {
        Loge("glfw init failed");
        exit(1);
    }

    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
    window_ = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window_) {
        glfwTerminate();
        Loge("window create failed");
        exit(2);
    }

    glfwMakeContextCurrent(window_);

    gladLoadGL();
    glfwSwapInterval(1);

    glViewport(0, 0, 640, 480);
}

void Context::Quit() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}

void Context::SwapBuffers() {
    glfwSwapBuffers(window_);
}

bool Context::ShouldClose() {
    return glfwWindowShouldClose(window_);
}

}