#include "engine/core/pch.hpp"
#include "engine/core/context.hpp"
#include "engine/renderer/renderer.hpp"

DLLEXPORT extern void GameLoop(void);

int main(int argc, char** argv) {
    engine::Context::Init("hello", 640, 480);

    engine::Renderer::SetClearColor(engine::Color(0.1, 0.1, 0.1, 1));
    while (!engine::Context::ShouldClose()) {
        /* Render here */
        engine::Renderer::Clear();

        /* Swap front and back buffers */
        engine::Context::SwapBuffers();

        GameLoop();

        /* Poll for and process events */
        glfwPollEvents();
    }

    engine::Context::Quit();
    return 0;
}