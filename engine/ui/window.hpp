#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"
#include "nuklear.h"

namespace engine {

class DLLEXPORT UIWindow final: public Component {
public:
    UIWindow(ComponentID id): Component(id) { Reset(); }
    void Reset() override;

    std::string title;
    nk_flags flags;
    Rect rect;
};

Entity* CreateUIWindow(const std::string& name, const std::string& title, nk_flags flags, const Rect& rect);

};