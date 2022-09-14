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
    DLLEXPORT static void Capture(bool);

private:
    static bool isShow_;
};

}