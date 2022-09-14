#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class UIText: public Component {
public:
    UIText(ComponentID id): Component(id) {}

    void Reset() override;

    int flags;
    std::string text; 
};

}