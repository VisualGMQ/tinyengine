#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class NodeComponent: public Component {
public:
    NodeComponent(ComponentID id, const std::string& name): Component(id, name) {}

    virtual void OnInit() { children.clear(); }
    virtual void OnQuit() {}

    std::vector<Entity*> children;
};

}