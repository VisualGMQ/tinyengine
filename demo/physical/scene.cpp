#include "engine/engine.hpp"
#include "move_behavior.hpp"

class StartScene final : public engine::Scene {
public:
    StartScene(const std::string& name): engine::Scene(name) {}

    void OnInit() override;
    void OnQuit() override;
};

void StartScene::OnInit() {
    auto entity1 = engine::World::Instance()->CreateEntity<engine::Node2DComponent, engine::BoxColliderComponent, engine::RigidBodyComponent>("entity1");
    entity1->SetBehavior(std::make_unique<MoveBehavior>(engine::Color(1, 0, 0), SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S));
    auto box = entity1->GetComponent<engine::BoxColliderComponent>();
    box->halfHeight = 20;
    box->halfWidth = 20;
    auto node2d = entity1->GetComponent<engine::Node2DComponent>();
    node2d->position.Set(100, 100);

    Attach2D(entity1);

    auto entity2 = engine::World::Instance()->CreateEntity<engine::Node2DComponent, engine::BoxColliderComponent, engine::RigidBodyComponent>("entity2");
    entity2->SetBehavior(std::make_unique<MoveBehavior>(engine::Color(0, 1, 0), SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN));
    box = entity2->GetComponent<engine::BoxColliderComponent>();
    box->halfHeight = 20;
    box->halfWidth = 20;
    node2d = entity2->GetComponent<engine::Node2DComponent>();
    node2d->position.Set(200, 200);

    Attach2D(entity2);
}

void StartScene::OnQuit() {

}

SCENE_CONFIG() {
    LOAD_SCENE(StartScene);
    ENTER_SCENE(StartScene);
}