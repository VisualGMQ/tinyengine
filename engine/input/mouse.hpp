#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/context.hpp"

namespace engine {

class DLLEXPORT Mouse final {
public:
    Mouse() = delete;

    DLLEXPORT static void Hide();
    DLLEXPORT static void Show();
    DLLEXPORT static bool IsShowing();

private:
    static bool isShow_;
};

}