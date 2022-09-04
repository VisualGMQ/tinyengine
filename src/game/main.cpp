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
#include "engine/ecs/world.hpp"
#include "engine/core/timer.hpp"
#include "engine/renderer/tilesheet.hpp"
#include "engine/ui/ui_system.hpp"

class MyComponent: public engine::Component {
public:
    MyComponent(unsigned int id, const std::string& name): engine::Component(id, name) {}

    void OnInit() override {
        Logt("init");
    }

    void OnQuit() override {
        Logt("quit");
    }

    int value = 123;
};

class TestSystem: public engine::System {
public:
    TestSystem(engine::World* world): engine::System(world) {}

    void Update() override {
        const auto& entities = World()->Entities();
        for (auto& entity : entities) {
            if (entity->GetComponent<MyComponent>()) {
                Logt1("entity has MyComponent");
            }
        }
    }
};

class TestBehavior: public engine::Behavior {
public:
    void OnInit() override {
        Logw("inited");
    }

    void OnUpdate() override {
        Logw1("update");
    }

    void OnQuit() override {
        Logw("quit");
    }
private:
};

class GameStart: public engine::Scene {
public:
    GameStart(const std::string& name): engine::Scene(name) {}
    void OnInit() override {
        world_ = engine::World::Instance();
        world_->AddSystem<TestSystem>();
        world_->AddSystem<engine::UISystem>();

        auto texture = engine::TextureFactory::Create("./resources/test.jpg", "test");

        trianglePrymaid_ = engine::CreateCubeMesh();
        engine::Mouse::Hide();
        engine::Renderer::GetPerspCamera()->MoveTo(engine::Vec3(0, 1, 1));

        entity_ = world_->CreateEntity("Entity1");
        entity_->SetBehavior(std::make_unique<TestBehavior>());
        entity_->SetComponent<MyComponent>(world_->CreateComponent<MyComponent>("MyComponent"));
        Logw("parent name = %s", entity_->GetComponent<MyComponent>()->Parent()->Name().c_str());

        engine::TimerID id = engine::Timer::AddTimer([](engine::Timer& timer, double time, void* param){
            static int tick = 0;
            tick++;
            Logi("ticked");
            if (tick == 5) {
                engine::Timer::RemoveTimer(timer.ID());
            }
            return time;
        }, 1, nullptr);

        texture = engine::TextureFactory::Create("./resources/tilesheet.png", "tilesheet");
        Logw("texture id = %d", texture->ID());
        tilesheet_.reset(new engine::TileSheet(texture->ID(), 3, 13));
        tile_ = tilesheet_->Get(0, 1);

        button_ = world_->CreateEntity("test button");
        button_->SetComponent(world_->CreateComponent<engine::RectTransform>("recttransform"));
        button_->SetComponent(world_->CreateComponent<engine::ButtonComponent>("buttonComponent"));

        cppImage_.reset(new engine::Image(engine::TextureFactory::Find("test")));
        button_->GetComponent<engine::RectTransform>()->position.Set(20, 40);
        button_->GetComponent<engine::RectTransform>()->anchor.Set(0, 0);
        button_->GetComponent<engine::RectTransform>()->size = cppImage_->GetSize();
        button_->GetComponent<engine::ButtonComponent>()->image = cppImage_;
        button_->GetComponent<engine::ButtonComponent>()->clickCb = [](engine::ButtonComponent*) {
            Logw("clicked");
        };
        button_->GetComponent<engine::ButtonComponent>()->motionCb = [](engine::ButtonComponent*) {
            Logw("motioned");
        };
    }
    void OnUpdate() override;
    void OnQuit() override {
        world_->Shutdown();
        trianglePrymaid_.reset();
    }

private:
    engine::Entity* entity_;
    engine::World* world_;
    std::shared_ptr<engine::Image> tile_;
    engine::Vec2 rotation_;
    std::shared_ptr<engine::Image> cppImage_;
    std::unique_ptr<engine::TileSheet> tilesheet_;
    engine::Entity* button_;
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
        if (engine::Input::IsKeyPressed(Key_M)) {
            if (engine::Mouse::IsShowing()) {
                engine::Mouse::Hide();
            } else {
                engine::Mouse::Show();
            }
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
        tile_->SetPosition(engine::Vec2(300, 300));
        tile_->Draw();


        engine::Renderer::SetDrawColor(engine::Color(1, 1, 1));
        engine::Renderer::DrawText("VisualGMQ made for 1MGames\ngithub: https://github.visualgmq.io\na simple framework makde for 1MGames", engine::Vec2(500, 0), 16);
        engine::Renderer::DrawText(".,\"':;/?!\n@#$%^&*()_+-=", engine::Vec2(500, 100), 32);
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
    world_->Update();
    world_->CleanUp();
}

SCENE_CONFIG() {
    LOAD_SCENE(GameStart);
    ENTER_SCENE(GameStart);
}
