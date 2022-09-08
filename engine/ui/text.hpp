#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class UIText: public Component {
public:
    UIText(ComponentID id, const std::string& name): Component(id, name) {}

    void Reset() override;

    int flags;
    std::string text; 
};

}