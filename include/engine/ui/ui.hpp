#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class UIBase: public Component {
public:
    UIBase(ComponentID id, const std::string& name): Component(id, name) {}
    void OnInit() override { shouldRaycast = true; }
    bool shouldRaycast;

    virtual ~UIBase() = default;

};

}
