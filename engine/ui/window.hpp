#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class DLLEXPORT UIWindow final: public Component {
public:
    UIWindow(ComponentID id, const std::string& name): Component(id, name) {}
    void Reset() override;

    std::string title;
    bool isShowTitle;
    uint32_t flags;
    Rect rect;
};

};