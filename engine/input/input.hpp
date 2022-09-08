#pragma once

#include "engine/core/pch.hpp"
#include "engine/input/keycode.hpp"
#include "engine/core/vmath.hpp"
#include "engine/core/context.hpp"

namespace engine {

class Input final {
public:
    Input() = delete;

    DLLEXPORT static void Init();
    DLLEXPORT static void Quit();

    DLLEXPORT static bool IsKeyPressed(KeyCode);
    DLLEXPORT static bool IsKeyPressing(KeyCode);
    DLLEXPORT static bool IsKeyReleased(KeyCode);
    DLLEXPORT static bool IsKeyReleasing(KeyCode);

    DLLEXPORT static bool IsButtonPressed(MouseButton);
    DLLEXPORT static bool IsButtonPressing(MouseButton);
    DLLEXPORT static bool IsButtonReleased(MouseButton);
    DLLEXPORT static bool IsButtonReleasing(MouseButton);

    DLLEXPORT static const Vec2& MousePoition();
    DLLEXPORT static const Vec2& MouseRelative();

    DLLEXPORT static void UpdateStates();

private:
    static bool oldKeyState_[KEY_NUM];
    static bool keyState_[KEY_NUM];
    static bool oldBtnState_[MOUSEBUTTON_NUM];
    static bool btnState_[MOUSEBUTTON_NUM];
    static Vec2 position_;
    static Vec2 offset_;
};

}
