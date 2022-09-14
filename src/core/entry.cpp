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
#include "engine/core/dllexport.hpp"
#include "engine/sound/sound.hpp"
#include "engine/renderer/font.hpp"
#include "engine/core/timer.hpp"

constexpr int WindowWidth = 800;
constexpr int WindowHeight = 600;

__declspec(dllexport) extern void GameInit(void);

void PollEvent(SDL_Event& event) {
    while (SDL_PollEvent(&event)) {
        engine::UI::HandleEvent(&event);
        if (event.type == SDL_QUIT) {
            engine::Context::Close();
        }
        if (event.type == SDL_KEYDOWN) {
            engine::Input::UpdateKeyState(event.key.keysym.scancode, true);
        }
        if (event.type == SDL_KEYUP) {
            engine::Input::UpdateKeyState(event.key.keysym.scancode, false);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            engine::Input::UpdateMouseBtnState(event.button.button, true);
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            engine::Input::UpdateMouseBtnState(event.button.button, false);
        }
        if (event.type == SDL_MOUSEMOTION) {
            engine::Input::UpdateMousePosition(engine::Vec2(event.motion.x, event.motion.y),
                                               engine::Vec2(event.motion.xrel, event.motion.yrel));
        }
        if (event.type == SDL_USEREVENT) {
            engine::Timer::Param* param =  (engine::Timer::Param*)event.user.data1;
            auto callback = param->owner->GetCallback();
            if (callback) {
                callback(*param->owner, param->owner->Interval(), param->userParam);
            }
        }
        if (event.type == SDL_WINDOWEVENT) {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                GL_CALL(glViewport(0, 0, event.window.data1, event.window.data2));
            }
        }
    }
}

int main(int argc, char** argv) {
    engine::Logger::Init();
    engine::Configer configReader("init.cfg");
    auto title = configReader.GetOr<std::string>("title", "engine");
    auto width = configReader.GetOr<float>("width", WindowWidth);
    auto height = configReader.GetOr<float>("height", WindowHeight);
    auto resizable = configReader.GetOr<bool>("resizable", false);

    engine::Context::Init(title, width, height, resizable);
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

    SDL_Event event;

    engine::Renderer::SetClearColor(engine::Color(0.1, 0.1, 0.1, 1));
    while (!engine::Context::ShouldClose()) {
        engine::UI::InputBegin();
        PollEvent(event);
        engine::UI::InputEnd();
        engine::Renderer::ResestState();
        engine::Renderer::Clear();
        engine::World::Instance()->TryInitEntities();
        if (auto scene = engine::SceneMgr::CurrentScene(); scene) {
            scene->OnUpdate();
        }
        engine::World::Instance()->Update();
        engine::UI::Update();
        engine::Timer::UpdateElapse();
        engine::Input::UpdateStates();
        engine::SceneMgr::QuitOldScene();
        engine::World::Instance()->CleanUp();
        engine::Context::SwapBuffers();
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
    engine::Context::Quit();
    engine::Logger::Quit();
    return 0;
}