#include "engine/core/context.hpp"

namespace engine {

GLFWwindow* Context::window_ = nullptr;


GLFWwindow* Context::GetWindow() {
    return window_;
}

void FramebufferResizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Context::Init(const std::string& title, int w, int h) {
    if (!glfwInit()) {
        Loge("glfw init failed");
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window_ = glfwCreateWindow(w, h, "Hello World", NULL, NULL);
    if (!window_) {
        glfwTerminate();
        Loge("window create failed");
        exit(2);
    }

    glfwMakeContextCurrent(window_);

    gladLoadGL();

    glViewport(0, 0, w, h);

    glfwSetFramebufferSizeCallback(window_, FramebufferResizeCallback);
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
