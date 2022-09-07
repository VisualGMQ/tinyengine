#include "engine/core/context.hpp"
#include "engine/core/configer.hpp"
#include "engine/core/scene.hpp"
#include "engine/input/input.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/core/timer.hpp"
#include "engine/ecs/world.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/ui/ui.hpp"

DLLEXPORT extern void GameInit(void);

constexpr int WindowWidth = 1024;
constexpr int WindowHeight = 720;

int main(int argc, char** argv) {
    engine::Configer configReader("init.cfg");
    auto title = configReader.GetOr<std::string>("title", "engine");
    auto width = configReader.GetOr<float>("width", WindowWidth);
    auto height = configReader.GetOr<float>("height", WindowHeight);

    engine::Logger::Init();
    engine::Context::Init(title, width, height);
    engine::Renderer::Init(width, height);
    engine::TextureFactory::Init();
    engine::UI::Init();
    engine::Input::Init();
    engine::World::Init();
    engine::SceneMgr::Init();

    GameInit();

    engine::Renderer::SetClearColor(engine::Color(0.1, 0.1, 0.1, 1));
    while (!engine::Context::ShouldClose()) {
        glfwPollEvents();
        engine::Renderer::ResestState();
        engine::Renderer::Clear();
        engine::World::Instance()->TryInitEntities();
        if (auto scene = engine::SceneMgr::CurrentScene(); scene) {
            scene->OnUpdate();
        }
        engine::World::Instance()->Update();
        engine::UI::Update();
        engine::Timer::UpdateElapse();
        engine::Timer::UpdateTimers();
        engine::Timer::CleanUpTimers();
        engine::Input::UpdateStates();
        engine::SceneMgr::QuitOldScene();
        engine::World::Instance()->CleanUp();
        engine::Context::SwapBuffers();
    }

    engine::SceneMgr::Quit();
    engine::World::Quit();
    engine::Input::Quit();
    engine::UI::Quit();
    engine::TextureFactory::Quit();
    engine::Renderer::Quit();
    engine::Context::Quit();
    engine::Logger::Quit();
    return 0;
}