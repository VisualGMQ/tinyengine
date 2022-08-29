#include "engine/core/log.hpp"
#include "engine/core/scene.hpp"
#include "engine/input/input.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/shader.hpp"

enum TextureID {
    Test = 1,
};

class GameStart: public engine::Scene {
public:
    GameStart(const std::string& name): engine::Scene(name) {}
    void OnInit() override {
        engine::TextureFactory::Create(Test, "./resources/test.jpg");
    }
    void OnUpdate() override;
    void OnQuit() override {}
};

void GameStart::OnUpdate(void) {
    engine::Renderer::SetDrawColor(engine::Color(1, 0, 0, 1));
    engine::Renderer::DrawLine(engine::Vec2(0, 0), engine::Vec2(1024, 720));
    engine::Renderer::SetDrawColor(engine::Color(0, 1, 0, 1));
    engine::Renderer::DrawRect(engine::Rect(100, 100, 200, 300));
    engine::Renderer::SetDrawColor(engine::Color(0, 0, 1, 1));
    engine::Renderer::FillRect(engine::Rect(100, 500, 200, 100));
    engine::Renderer::DrawLines({engine::Vec2(100, 100), engine::Vec2(200, 150), engine::Vec2(300, 400)});

    auto texture = engine::TextureFactory::Find(Test);
    engine::Renderer::DrawTexture(*texture, nullptr, engine::Rect(400, 100, texture->Width(), texture->Height()));
}

SCENE_CONFIG() {
    LOAD_SCENE(GameStart);
    ENTER_SCENE(GameStart);
}