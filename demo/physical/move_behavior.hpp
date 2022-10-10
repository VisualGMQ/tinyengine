#pragma once

#include "engine/engine.hpp"

constexpr float force = 100;

class MoveBehavior: public engine::Behavior {
public:
    MoveBehavior(const engine::Color& color, SDL_Scancode leftKey, SDL_Scancode rightKey, SDL_Scancode upKey, SDL_Scancode downKey);

    void OnInit() override;
    void OnUpdate() override;
    void OnQuit() override;

private:
    engine::Color color_;
    SDL_Scancode leftKey_;
    SDL_Scancode rightKey_;
    SDL_Scancode upKey_;
    SDL_Scancode downKey_;
};


MoveBehavior::MoveBehavior(const engine::Color& color, SDL_Scancode leftKey, SDL_Scancode rightKey, SDL_Scancode upKey, SDL_Scancode downKey)
    : color_(color), leftKey_(leftKey), rightKey_(rightKey), upKey_(upKey), downKey_(downKey) {}

void MoveBehavior::OnInit() {

}

void MoveBehavior::OnUpdate() {
    auto node2d = Parent()->GetComponent<engine::Node2DComponent>();
    auto box = Parent()->GetComponent<engine::BoxColliderComponent>();

    engine::Renderer::SetDrawColor(color_);
    engine::Renderer::DrawRect(engine::Rect(node2d->position.x - box->halfWidth + box->offset.x,
                                            node2d->position.y - box->halfHeight + box->offset.y,
                                            box->halfWidth * 2, box->halfHeight * 2));

    engine::Vec2 realForce;
    if (engine::Input::IsKeyPressing(leftKey_)) {
        realForce += engine::Vec2(-force, 0) ;
    }
    if (engine::Input::IsKeyPressing(rightKey_)) {
        realForce += engine::Vec2(force, 0) ;
    }
    if (engine::Input::IsKeyPressing(upKey_)) {
        realForce += engine::Vec2(0, -force) ;
    }
    if (engine::Input::IsKeyPressing(downKey_)) {
        realForce += engine::Vec2(0, force) ;
    }

    auto rigid = Parent()->GetComponent<engine::RigidBodyComponent>();
    rigid->force = realForce;
}

void MoveBehavior::OnQuit() {

}