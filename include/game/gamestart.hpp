#pragma once
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
#include "engine/ecs/world.hpp"
#include "engine/renderer/image.hpp"
#include "engine/core/timer.hpp"
#include "engine/renderer/tilesheet.hpp"
#include "engine/ui/ui_system.hpp"
#include "engine/ui/window.hpp"
#include "engine/ui/button.hpp"
#include "engine/ui/checkbox.hpp"
#include "engine/ui/layout.hpp"

class MyComponent: public engine::Component {
public:
    MyComponent(unsigned int id, const std::string& name): engine::Component(id, name) {}

    void Reset() override {
        Logt("component reset");
    }

    int value = 123;
};

class TestSystem: public engine::System {
public:
    TestSystem(engine::World* world): engine::System(world) {}

    void Update(engine::Entity* entity) override {
        if (entity->GetComponent<MyComponent>()) {
            Logt1("entity has MyComponent");
        }
    }
};

class TestBehavior: public engine::Behavior {
public:
    void OnInit() override {
        Logw("behavior init");
    }

    void OnUpdate() override {
        Logw1("behavior update");
    }

    void OnQuit() override {
        Logw("behavior quit");
    }
private:
};

class GameStart: public engine::Scene {
public:
    GameStart(const std::string& name): engine::Scene(name) {}
    void OnInit() override {
        engine::World* world = engine::World::Instance();
        world = engine::World::Instance();
        world->AddSystem<TestSystem>();

        auto texture = engine::TextureFactory::Create("./resources/test.jpg", "test");

        trianglePrymaid_ = engine::CreateCubeMesh();
        // engine::Mouse::Hide();
        engine::Renderer::GetPerspCamera()->MoveTo(engine::Vec3(0, 1, 1));

        auto entity = world->CreateEntity("Entity1");
        entity->SetBehavior(std::make_unique<TestBehavior>());
        entity->SetComponent(world->CreateComponent<MyComponent>("MyComponent"));
        Attach(entity);

        auto windowEntity = world->CreateEntity("WindowEntity");
        auto uiwindow = world->CreateComponent<engine::UIWindow>("window");
        windowEntity->SetComponent(uiwindow);
        uiwindow->title = "Demo";
        uiwindow->rect.position.Set(50, 50);
        uiwindow->rect.size.Set(230, 250);
        uiwindow->flags = NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                          NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE;
        auto node = world->CreateComponent<engine::NodeComponent>("window node");
        windowEntity->SetComponent(node);
        Attach(windowEntity);

        auto layout = world->CreateEntity("layout");
        auto rowLayout = world->CreateComponent<engine::UIDynamicRowLayout>("rowlayout");
        auto layoutNode = world->CreateComponent<engine::NodeComponent>("layout node");
        rowLayout->cols = 2;
        rowLayout->height = 50;
        layout->SetComponent(rowLayout);
        layout->SetComponent(layoutNode);

        node->Attach(layout);

        auto buttonEntity = world->CreateEntity("button");
        auto button = world->CreateComponent<engine::UIButton>("button");
        buttonEntity->SetComponent(button);
        layoutNode->Attach(buttonEntity);

        auto checkboxEntity = world->CreateEntity("checkbox");
        auto checkbox = world->CreateComponent<engine::UICheckbox>("checkbox");
        checkbox->text = "checkbox 1";
        checkbox->isSelected = false;
        checkbox->callback = [](engine::Entity* self) {
            Logt("clicked checkbox");
            auto& select = self->GetComponent<engine::UICheckbox>()->isSelected;
            select = !select;
        };
        checkboxEntity->SetComponent(checkbox);
        layoutNode->Attach(checkboxEntity);

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
        Logw("texture id = {}", texture->ID());
        tilesheet_.reset(new engine::TileSheet(texture->ID(), 3, 13));
        tile1_ = tilesheet_->Get(0, 1);
        tile2_ = tilesheet_->Get(0, 2);
        tile3_ = tilesheet_->Get(0, 3);

        cppImage_.reset(new engine::Image(engine::TextureFactory::Find("test")));
    }
    void OnUpdate() override;
    void OnQuit() override {
        trianglePrymaid_.reset();
    }

private:
    std::shared_ptr<engine::Image> tile1_;
    std::shared_ptr<engine::Image> tile2_;
    std::shared_ptr<engine::Image> tile3_;
    engine::Vec2 rotation_;
    std::shared_ptr<engine::Image> cppImage_;
    std::unique_ptr<engine::TileSheet> tilesheet_;
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
        engine::Renderer::SetDrawColor(engine::Color(0, 1, 0));
        engine::Renderer::DrawRect(engine::Rect(100, 100, 200, 300));
        engine::Renderer::SetDrawColor(engine::Color(0, 0, 1));
        engine::Renderer::FillRect(engine::Rect(100, 500, 200, 100));
        engine::Renderer::DrawLines({engine::Vec2(100, 100), engine::Vec2(200, 150), engine::Vec2(300, 400)});

        engine::Renderer::SetDrawColor(engine::Color(1, 1, 1));
        tile1_->SetPosition(engine::Vec2(300, 300));
        tile1_->Draw();
        tile2_->SetPosition(engine::Vec2(350, 300));
        tile2_->Draw();
        tile3_->SetPosition(engine::Vec2(400, 300));
        tile3_->Draw();

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