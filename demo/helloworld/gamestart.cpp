#include "gamestart.hpp"

void GameStart::OnUpdate() {
    if (engine::Input::IsKeyPressed(Key_C)) {
        engine::SceneMgr::ChangeScene("UIScene");
        engine::Mouse::Show();
    }
    engine::Renderer::Begin3D();
    draw3d();
    engine::Renderer::Begin2D();
    draw2d();
    update3d();
    // update2d();
}