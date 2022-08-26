#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/vmath.hpp"

namespace engine {

class Renderer final {
public:
    static void SetClearColor(const Color& color);
    static void Clear();
};

}