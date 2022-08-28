#include "engine/core/pch.hpp"
#include "engine/core/context.hpp"
#include "engine/input/input.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/texture.hpp"

DLLEXPORT extern void GameLoop(void);
DLLEXPORT extern void GameInit(void);
DLLEXPORT extern void GameQuit(void);

constexpr int WindowWidth = 1024;
constexpr int WindowHeight = 720;

int main(int argc, char** argv) {
    engine::Context::Init("hello", WindowWidth, WindowHeight);
    engine::Renderer::Init(WindowWidth, WindowHeight);
    engine::TextureFactory::Init();
    engine::Input::Init();

    GameInit();

    engine::Renderer::SetClearColor(engine::Color(0.1, 0.1, 0.1, 1));
    while (!engine::Context::ShouldClose()) {
        glfwPollEvents();
        engine::Renderer::Clear();
        GameLoop();
        engine::Context::SwapBuffers();
        engine::Input::UpdateStates();
    }

    GameQuit();

    engine::Input::Quit();
    engine::TextureFactory::Quit();
    engine::Renderer::Quit();
    engine::Context::Quit();
    return 0;
}
