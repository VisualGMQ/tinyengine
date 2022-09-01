#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class BehaviorComponent: public Component {
public:
    BehaviorComponent(const std::string& name): Component(name) {}
};

}