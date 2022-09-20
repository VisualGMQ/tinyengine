#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"
#include "nuklear.h"

namespace engine {

class DLLEXPORT UIGroup final: public Component {
public:
    UIGroup(ComponentID id) : Component(id) { Reset(); }
    void Reset() override;

    std::string title;
    nk_flags options;
};

Entity* CreateUIGroup(const std::string& name, const std::string& title, nk_flags options, Entity* parent);

};