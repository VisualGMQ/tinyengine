#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class DLLEXPORT UICheckbox: public Component {
public:
    UICheckbox(ComponentID id): Component(id) {}
    void Reset() override;

    bool isSelected;
    std::string text;
    std::function<void(Entity*)> callback;
};

}