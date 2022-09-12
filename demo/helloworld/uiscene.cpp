#include "uiscene.hpp"

void UIScene::OnInit() {
}

void UIScene::OnUpdate() {
    if (engine::Input::IsKeyPressed(SDL_SCANCODE_C)) {
        engine::SceneMgr::ChangeScene("GameStart");
    }

}

void UIScene::OnQuit() {
}