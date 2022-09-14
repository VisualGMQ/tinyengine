#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class DLLEXPORT UIWindow final: public Component {
public:
    UIWindow(ComponentID id): Component(id) {}
    void Reset() override;

    std::string title;
    uint32_t flags;
    Rect rect;
};

};