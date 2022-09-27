#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"
#include "nuklear.h"

namespace engine {

class UILabel: public Component {
public:
    UILabel(ComponentID id) : Component(id) { Reset(); }
    void Reset() override;

    std::string text;
    nk_flags align;
    bool wrap;
};

Entity* CreateUILabel(const std::string& name, const std::string& text, nk_flags align, Entity* parent);

}
