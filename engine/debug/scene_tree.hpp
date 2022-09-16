#pragma once

#include "engine/ecs/component.hpp"
#include "engine/core/scene.hpp"
#include "engine/ui/tree.hpp"

namespace engine::debug {

class UISceneTree: public Component {
public:
    UISceneTree(ComponentID id): Component(id) {}

    void Reset() override {}

    void Update();

    engine::Entity* root;

private:
    void doUpdate(engine::Entity* sceneNode, engine::Entity* parentNode);
};

}