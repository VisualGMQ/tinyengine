#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class UIButton: public Component {
public:
    UIButton(ComponentID id, const std::string& name): Component(id, name) {}

    void Reset() override;

    std::string text;
    std::function<void(Entity*)> onClick;
};

}