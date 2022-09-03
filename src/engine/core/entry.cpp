#include "engine/core/context.hpp"
#include "engine/core/configer.hpp"
#include "engine/core/scene.hpp"
#include "engine/input/input.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/core/timer.hpp"

DLLEXPORT extern void GameInit(void);

constexpr int WindowWidth = 1024;
constexpr int WindowHeight = 720;

int main(int argc, char** argv) {
    engine::Configer configReader("init.cfg");
    auto titleElem = configReader.Get<std::string>("title");
    auto widthElem = configReader.Get<float>("width");
    auto heightElem = configReader.Get<float>("height");

    std::string title = titleElem ? titleElem.value() : "engine";
    float width = widthElem ? widthElem.value() : 1024;
    float height = heightElem ? heightElem.value() : 720;

    engine::Context::Init(title, width, height);
    engine::Renderer::Init(width, height);
    engine::TextureFactory::Init();
    engine::Input::Init();
    engine::SceneMgr::Init();

    GameInit();

    engine::Scene* scene = engine::SceneMgr::CurrentScene();

    engine::Renderer::SetClearColor(engine::Color(0.1, 0.1, 0.1, 1));
    while (!engine::Context::ShouldClose()) {
        glfwPollEvents();
        engine::Renderer::Clear();
        scene->OnUpdate();
        engine::Timer::UpdateElapse();
        engine::Timer::UpdateTimers();
        engine::Timer::CleanUpTimers();
        engine::Context::SwapBuffers();
        engine::Input::UpdateStates();
        engine::SceneMgr::QuitOldScene();
    }

    engine::SceneMgr::Quit();
    engine::Input::Quit();
    engine::TextureFactory::Quit();
    engine::Renderer::Quit();
    engine::Context::Quit();
    return 0;
}
