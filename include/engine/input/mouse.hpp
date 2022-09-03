#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/context.hpp"

namespace engine {

class Mouse final {
public:
    static void Hide();
    static void Show();
    static bool IsShowing();
};

}