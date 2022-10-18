#include "3d_draw.hpp"

void Draw3DBehavior::OnInit() {
    cube_ = engine::CreateCubeMesh();
    lineRotationY_ = 0;
    rotation_.Set(0, 0);
}

void Draw3DBehavior::OnUpdate() {
    auto camera = engine::Renderer::GetPerspCamera();
    if (engine::Input::IsKeyPressing(SDL_SCANCODE_W)) {
        camera->MoveFront(0.01);
    }
    if (engine::Input::IsKeyPressing(SDL_SCANCODE_S)) {
        camera->MoveFront(-0.01);
    }
    if (engine::Input::IsKeyPressing(SDL_SCANCODE_A)) {
        camera->MoveRight(-0.01);
    }
    if (engine::Input::IsKeyPressing(SDL_SCANCODE_D)) {
        camera->MoveRight(0.01);
    }
    if (engine::Input::IsKeyPressing(SDL_SCANCODE_Q)) {
        camera->MoveUp(0.01);
    }
    if (engine::Input::IsKeyPressing(SDL_SCANCODE_E)) {
        camera->MoveUp(-0.01);
    }
    if (engine::Input::IsKeyPressed(SDL_SCANCODE_M)) {
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

    if (engine::Input::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
        engine::Video::Close();
    }

    engine::Renderer::SetDrawColor(engine::Color(0, 1, 0));
    engine::Renderer::DrawMeshFrame(*cube_, engine::CreateIdentityMat<4>());
    engine::Renderer::SetDrawColor(engine::Color(0.5, 0.5, 0.5));
    engine::Renderer::DrawGrid();
    engine::Renderer::SetDrawColor(engine::Color(1, 0, 0));
    engine::Renderer::DrawLine(engine::RotateWithQuat(engine::Vec3(-0.5, 0.1, -1), lineRotationY_, engine::Vec3(0, 1, 0)),
                               engine::RotateWithQuat(engine::Vec3(0.5, 0.1, -1), lineRotationY_, engine::Vec3(0, 1, 0)));

}

void Draw3DBehavior::OnQuit() {
    cube_.reset();
}