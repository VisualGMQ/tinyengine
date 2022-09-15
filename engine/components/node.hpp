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


class Node2DRoot: public Component {
public:
    Node2DRoot(ComponentID id): Component(id) {}
    void Reset() override {}
};

class Node3DRoot: public Component {
public:
    Node3DRoot(ComponentID id): Component(id) {}
    void Reset() override {}
};

class NodeUIRoot final: public Component {
public:
    NodeUIRoot(ComponentID id): Component(id) {}
    void Reset() override {}
};

}