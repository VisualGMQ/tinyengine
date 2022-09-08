#pragma once

#include "engine/core/pch.hpp"
#include "engine/input/keycode.hpp"
#include "engine/core/vmath.hpp"
#include "engine/core/context.hpp"

namespace engine {

class DLLEXPORT Input final {
public:
    Input() = delete;

    static void Init();
    static void Quit();

    static bool IsKeyPressed(KeyCode);
    static bool IsKeyPressing(KeyCode);
    static bool IsKeyReleased(KeyCode);
    static bool IsKeyReleasing(KeyCode);

    static bool IsButtonPressed(MouseButton);
    static bool IsButtonPressing(MouseButton);
    static bool IsButtonReleased(MouseButton);
    static bool IsButtonReleasing(MouseButton);

    static const Vec2& MousePoition();
    static const Vec2& MouseRelative();

    static void UpdateStates();

private:
    static bool oldKeyState_[KEY_NUM];
    static bool keyState_[KEY_NUM];
    static bool oldBtnState_[MOUSEBUTTON_NUM];
    static bool btnState_[MOUSEBUTTON_NUM];
    static Vec2 position_;
    static Vec2 offset_;
};

}
