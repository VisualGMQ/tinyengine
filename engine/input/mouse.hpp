#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/video.hpp"

namespace engine {

class DLLEXPORT Mouse final {
public:
    Mouse() = delete;

    DLLEXPORT static void Hide();
    DLLEXPORT static void Show();
    DLLEXPORT static bool IsShowing();
    DLLEXPORT static void ToggleShow();
    DLLEXPORT static void Capture(bool);
    DLLEXPORT static void RelativeMode(bool);
    DLLEXPORT static bool IsRelativeMode();
    DLLEXPORT static void ToggleRelativeMode();

private:
    static bool isShow_;
};

}