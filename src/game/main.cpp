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
        trianglePrymaid_ = engine::CreateTriangularPyramid();
    }
    void OnUpdate() override;
    void OnQuit() override {
        trianglePrymaid_.reset();
    }

private:
    engine::Vec3 position_;

    void update3d() {
        if (engine::Input::IsKeyPressing(Key_W)) {
            position_.z -= 0.01;
        }
        if (engine::Input::IsKeyPressing(Key_S)) {
            position_.z += 0.01;
        }
        if (engine::Input::IsKeyPressing(Key_A)) {
            position_.x -= 0.01;
        }
        if (engine::Input::IsKeyPressing(Key_D)) {
            position_.x += 0.01;
        }
    }

    void update2d() {
        auto& orthoCamera = engine::Renderer::GetOrthoCamera();
        if (engine::Input::IsKeyPressing(Key_A)) {
            orthoCamera->Move(engine::Vec3(-0.1, 0, 0));
        }
        if (engine::Input::IsKeyPressing(Key_D)) {
            orthoCamera->Move(engine::Vec3(0.1, 0, 0));
        }
    }

    void draw2d() {
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

    void draw3d() {
        engine::Renderer::SetDrawColor(engine::Color(0, 1, 0));
        engine::Renderer::DrawMeshFrame(*trianglePrymaid_, engine::CreateTranslate(position_));
    }

    std::shared_ptr<engine::Mesh> trianglePrymaid_;
};

void GameStart::OnUpdate(void) {
    engine::Renderer::Begin3D();
    draw3d();
    engine::Renderer::Begin2D();
    draw2d();
    update3d();
    // update2d();
}

SCENE_CONFIG() {
    LOAD_SCENE(GameStart);
    ENTER_SCENE(GameStart);
}
