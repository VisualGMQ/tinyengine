#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class DLLEXPORT NodeComponent: public Component {
public:
    NodeComponent(ComponentID id, const std::string& name): Component(id, name) {}

    std::vector<Entity*> children;
};

}
