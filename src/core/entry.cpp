#include "engine/core/video.hpp"
#include "engine/core/configer.hpp"
#include "engine/core/scene.hpp"
#include "engine/input/input.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/core/timer.hpp"
#include "engine/ecs/world.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/ui/ui.hpp"
#include "engine/core/dllexport.hpp"
#include "engine/sound/sound.hpp"
#include "engine/renderer/font.hpp"
#include "engine/core/timer.hpp"
#include "engine/core/event.hpp"

constexpr int WindowWidth = 800;
constexpr int WindowHeight = 600;

__declspec(dllexport) extern void GameInit(void);

int main(int argc, char** argv) {
    engine::Logger::Init();

    engine::Configer configReader("init.cfg");
    auto title = configReader.GetOr<std::string>("title", "engine");
    auto width = configReader.GetOr<float>("width", WindowWidth);
    auto height = configReader.GetOr<float>("height", WindowHeight);
    auto resizable = configReader.GetOr<bool>("resizable", false);

    engine::Video::Init(title, width, height, resizable);
    engine::Event::Init();
    engine::Renderer::Init(width, height);
    engine::FontFactory::Init();
    engine::TextureFactory::Init();
    engine::UI::Init();
    engine::Input::Init();
    engine::Sound::Init();
    engine::SoundFactory::Init();
    engine::TimerFactory::Init();
    engine::World::Init();
    engine::SceneMgr::Init();

    GameInit();

    engine::Renderer::SetClearColor(engine::Color(0.1, 0.1, 0.1, 1));
    while (!engine::Video::ShouldClose()) {
        engine::Event::HandleEvent();

        engine::Renderer::ResestState();
        engine::Renderer::Clear();
        engine::World::Instance()->TryInitEntities();
        engine::World::Instance()->Update();
        engine::UI::Update();
        engine::Timer::UpdateElapse();
        engine::Input::UpdateStates();
        engine::SceneMgr::QuitOldScene();
        engine::World::Instance()->CleanUp();
        engine::Event::ClearState();
        engine::Video::SwapBuffers();
    }

    engine::SceneMgr::Quit();
    engine::World::Quit();
    engine::TimerFactory::Quit();
    engine::SoundFactory::Quit();
    engine::Sound::Quit();
    engine::Input::Quit();
    engine::UI::Quit();
    engine::TextureFactory::Quit();
    engine::FontFactory::Quit();
    engine::Renderer::Quit();
    engine::Event::Quit();
    engine::Video::Quit();
    engine::Logger::Quit();
    return 0;
}