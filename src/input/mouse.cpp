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
    return isShow_ || IsRelativeMode();
}

void Mouse::Capture(bool enable) {
    SDL_CaptureMouse(enable ? SDL_TRUE : SDL_FALSE);
}

void Mouse::RelativeMode(bool enable) {
    SDL_SetRelativeMouseMode(enable ? SDL_TRUE : SDL_FALSE);
}

bool Mouse::IsRelativeMode() {
    return SDL_GetRelativeMouseMode();
}

void Mouse::ToggleRelativeMode() {
    if (IsRelativeMode()) {
        RelativeMode(false);
    } else {
        RelativeMode(true);
    }
}

void Mouse::ToggleShow() {
    if (IsShowing()) {
        Hide();
    } else {
        Show();
    }
}

}