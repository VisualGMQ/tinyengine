#include "engine/core/log.hpp"
#include "engine/core/scene.hpp"
#include "engine/core/configer.hpp"
#include "engine/input/input.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/renderer/shader.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/input/mouse.hpp"
#include "engine/ecs/component.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/renderer/image.hpp"

enum TextureID {
    Test = 1,
};

class MyComponent: public engine::Component {
public:
    MyComponent(const std::string& name): engine::Component(name) {}

    void OnInit() override {
        Logt("init");
    }

    void OnUpdate() override {
        Logt("update");
    }

    void OnQuit() override {
        Logt("quit");
    }
};

class GameStart: public engine::Scene {
public:
    GameStart(const std::string& name): engine::Scene(name) {}
    void OnInit() override {
        auto texture = engine::TextureFactory::Create(Test, "./resources/test.jpg");
        image_ = std::make_unique<engine::Image>(texture);

        trianglePrymaid_ = engine::CreateCubeMesh();
        entity_ = engine::CreateEntity("first entity");
        entity_->SetComponent<MyComponent>(engine::ComponentFactory::Create<MyComponent>("MyComponent1"));
        entity_->RemoveComponent<MyComponent>();
        entity_->GetComponent<MyComponent>() ? Logt("don't remove") : Logt("removed");
        engine::Mouse::Hide();
        engine::Renderer::GetPerspCamera()->MoveTo(engine::Vec3(0, 1, 1));

        auto entity = engine::CreateEntity("entity1");
        entity->SetComponent<MyComponent>(engine::ComponentFactory::Create<MyComponent>("MyComponent"));
        Logw("parent name = %s", entity->GetComponent<MyComponent>()->Parent()->Name().c_str());
        entity->RemoveComponent<MyComponent>();
        Logw("has parent? %d", entity->GetComponent<MyComponent>() != nullptr);
    }
    void OnUpdate() override;
    void OnQuit() override {
        trianglePrymaid_.reset();
    }

private:
    std::shared_ptr<engine::Entity> entity_;
    std::unique_ptr<engine::Image> image_;
    engine::Vec2 rotation_;
    float lineRotationY_ = 0;

    void update3d() {
        auto camera = engine::Renderer::GetPerspCamera();
        if (engine::Input::IsKeyPressing(Key_W)) {
            camera->MoveFront(0.01);
        }
        if (engine::Input::IsKeyPressing(Key_S)) {
            camera->MoveFront(-0.01);
        }
        if (engine::Input::IsKeyPressing(Key_A)) {
            camera->MoveRight(-0.01);
        }
        if (engine::Input::IsKeyPressing(Key_D)) {
            camera->MoveRight(0.01);
        }
        if (engine::Input::IsKeyPressing(Key_Q)) {
            camera->MoveUp(0.01);
        }
        if (engine::Input::IsKeyPressing(Key_E)) {
            camera->MoveUp(-0.01);
        }
        if (engine::Input::IsKeyPressing(Key_H)) {
            lineRotationY_ -= 0.01;
        }
        if (engine::Input::IsKeyPressing(Key_L)) {
            lineRotationY_ += 0.01;
        }
        rotation_.y -= engine::Input::MouseRelative().x * 0.001;
        rotation_.x -= engine::Input::MouseRelative().y * 0.001;
        rotation_.x = engine::Clamp<double>(rotation_.x, -engine::PI / 2 + 0.01, engine::PI / 2 - 0.01);

        camera->RotateTo(rotation_.x, rotation_.y);

        if (engine::Input::IsKeyPressed(Key_Escape)) {
            engine::Context::Close();
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
        engine::Renderer::SetDrawColor(engine::Color(1, 0, 0));
        engine::Renderer::DrawLine(engine::Vec2(0, 0), engine::Vec2(1024, 720));
        engine::Renderer::SetDrawColor(engine::Color(0, 1, 0));
        engine::Renderer::DrawRect(engine::Rect(100, 100, 200, 300));
        engine::Renderer::SetDrawColor(engine::Color(0, 0, 1));
        engine::Renderer::FillRect(engine::Rect(100, 500, 200, 100));
        engine::Renderer::DrawLines({engine::Vec2(100, 100), engine::Vec2(200, 150), engine::Vec2(300, 400)});

        engine::Renderer::SetDrawColor(engine::Color(1, 1, 1));
        image_->SetPosition(engine::Vec2(100, 100));
        image_->Draw();
        // auto texture = engine::TextureFactory::Find(Test);
        // engine::Renderer::DrawTexture(*texture,
        //                               nullptr, engine::Size(texture->Width(), texture->Height()),
        //                               engine::CreateTranslate(engine::Vec3(100, 0, 0)) *
        //                               engine::CreateAxisRotationWithEular(engine::Vec3(0, 0, 1), engine::Radians(45)));
    }

    void draw3d() {
        engine::Renderer::SetDrawColor(engine::Color(0, 1, 0));
        engine::Renderer::DrawMeshFrame(*trianglePrymaid_, engine::CreateIdentityMat<4>());
        engine::Renderer::SetDrawColor(engine::Color(0.5, 0.5, 0.5));
        engine::Renderer::DrawGrid();
        engine::Renderer::SetDrawColor(engine::Color(1, 0, 0));
        engine::Renderer::DrawLine(engine::RotateWithQuat(engine::Vec3(-0.5, 0.1, -1), lineRotationY_, engine::Vec3(0, 1, 0)),
                                   engine::RotateWithQuat(engine::Vec3(0.5, 0.1, -1), lineRotationY_, engine::Vec3(0, 1, 0)));
    }

    std::shared_ptr<engine::Mesh> trianglePrymaid_;
};

void GameStart::OnUpdate() {
    engine::Renderer::Begin3D();
    draw3d();
    engine::Renderer::Begin2D();
    draw2d();
    update3d();
    // update2d();
    entity_->Update();
}

SCENE_CONFIG() {
    LOAD_SCENE(GameStart);
    ENTER_SCENE(GameStart);
}
