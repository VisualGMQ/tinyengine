#pragma once

#include "engine/ecs/component.hpp"
#include "engine/core/dllexport.hpp"

namespace engine {

class DLLEXPORT NodeComponent: public Component {
public:
    NodeComponent(ComponentID id): Component(id) {}

    virtual void Reset() override { children.clear(); }

    void Attach(Entity* entity) { children.push_back(entity); }

    std::vector<Entity*> children;
};

}