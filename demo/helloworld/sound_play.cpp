#include "sound_play.hpp"


void SoundBehavior::OnInit() {
    sound1_ = engine::SoundFactory::Find("test1");
    sound2_ = engine::SoundFactory::Find("test2");
}

void SoundBehavior::OnUpdate() {
    if (engine::Input::IsKeyPressed(SDL_SCANCODE_0))  {
        sound1_->Play();
    }
    if (engine::Input::IsKeyPressed(SDL_SCANCODE_1)) {
        sound2_->Play();
    }
}

void SoundBehavior::OnQuit() {

}