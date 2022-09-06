#include "engine/core/context.hpp"
#include "engine/core/configer.hpp"
#include "engine/core/scene.hpp"
#include "engine/input/input.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/core/timer.hpp"
#include "engine/ecs/world.hpp"
#include "engine/ecs/entity.hpp"

DLLEXPORT extern void GameInit(void);

constexpr int WindowWidth = 1024;
constexpr int WindowHeight = 720;

int main(int argc, char** argv) {
    engine::Configer configReader("init.cfg");
    auto titleElem = configReader.Get<std::string>("title");
    auto widthElem = configReader.Get<float>("width");
    auto heightElem = configReader.Get<float>("height");

    std::string title = titleElem ? titleElem.value() : "engine";
    float width = widthElem ? widthElem.value() : WindowWidth;
    float height = heightElem ? heightElem.value() : WindowHeight;

    engine::Logger::Init();
    engine::Context::Init(title, width, height);
    engine::Renderer::Init(width, height);
    engine::TextureFactory::Init();
    engine::Input::Init();
    engine::World::Init();
    engine::SceneMgr::Init();

    GameInit();

    engine::Renderer::SetClearColor(engine::Color(0.1, 0.1, 0.1, 1));
    while (!engine::Context::ShouldClose()) {
        glfwPollEvents();
        engine::Renderer::Clear();
        engine::World::Instance()->TryInitEntities();
        engine::SceneMgr::CurrentScene()->OnUpdate();
        engine::Timer::UpdateElapse();
        engine::Timer::UpdateTimers();
        engine::Timer::CleanUpTimers();
        engine::Input::UpdateStates();
        engine::World::Instance()->Update();
        engine::SceneMgr::QuitOldScene();
        engine::World::Instance()->CleanUp();
        engine::Context::SwapBuffers();
    }

    engine::SceneMgr::Quit();
    engine::World::Quit();
    engine::Input::Quit();
    engine::TextureFactory::Quit();
    engine::Renderer::Quit();
    engine::Context::Quit();
    engine::Logger::Quit();
    return 0;
}
