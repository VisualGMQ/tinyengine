#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"

namespace engine {

class UIText: public Component {
public:
    UIText(ComponentID id) : Component(id) { Reset(); }

    void Reset() override;

    int flags;
    std::string text; 
};

Entity* CreateUIText(const std::string& name, const std::string& text, int flags, Entity* parent);

}