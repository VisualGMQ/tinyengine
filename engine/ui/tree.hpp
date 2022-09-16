#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"
#include "nuklear.h"

namespace engine {

class UITree: public Component {
public:
    UITree(ComponentID id): Component(id), treeID_(curId_++) {}

    void Reset() override;
    int TreeID() const { return treeID_; }

    std::string text;
    nk_tree_type type;
    nk_collapse_states state;

private:
    static int curId_;
    int treeID_;
};

Entity* CreateUITreeTab(const std::string& name, const std::string& text, nk_collapse_states state, Entity* parent);
Entity* CreateUITreeNode(const std::string& name, const std::string& text, nk_collapse_states state, Entity* parent);

}