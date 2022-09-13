#pragma once

#include "engine/ecs/component.hpp"
#include "nuklear.h"

namespace engine {

class UITree: public Component {
public:
    UITree(ComponentID id, const std::string& name): Component(id, name), treeID_(curId_++) {}

    void Reset() override;
    int TreeID() const { return treeID_; }

    std::string text;
    nk_tree_type type;
    nk_collapse_states state;

private:
    static int curId_;
    int treeID_;
};

}