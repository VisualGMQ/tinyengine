#include "engine/input/mouse.hpp"

namespace engine {

bool Mouse::isShow_ = true;

void Mouse::Hide() {
    isShow_ = false;
    SDL_ShowCursor(false);
}

void Mouse::Show() {
    isShow_ = true;
    SDL_ShowCursor(true);
}

bool Mouse::IsShowing() {
    return isShow_;
}

}