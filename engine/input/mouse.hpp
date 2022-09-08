#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/context.hpp"

namespace engine {

class DLLEXPORT Mouse final {
public:
    Mouse() = delete;

    static void Hide();
    static void Show();
    static bool IsShowing();
};

}