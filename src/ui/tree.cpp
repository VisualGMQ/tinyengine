#include "engine/ui/tree.hpp"

namespace engine {

int UITree::curId_ = 0;

void UITree::Reset() {
    Component::Reset();
    type = NK_TREE_TAB;
    state = NK_MINIMIZED;
    text = "tree node";
    treeID_ = curId_++;
}

Entity* CreateUITreeTab(const std::string& name, const std::string& text, nk_collapse_states state, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity<UITree, NodeComponent>(name);
    auto tree = entity->GetComponent<UITree>();
    tree->state = state;
    tree->text = text;
    tree->type = NK_TREE_TAB;

    if (parent) {
        auto node = parent->GetComponent<NodeComponent>();
        if (!node) {
            node = World::Instance()->CreateComponent<NodeComponent>();
            parent->SetComponent(node);
        }
        node->Attach(entity);
    }
    return entity;
}

Entity* CreateUITreeNode(const std::string& name, const std::string& text, nk_collapse_states state, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity<UITree, NodeComponent>(name);
    auto tree = entity->GetComponent<UITree>();
    tree->state = state;
    tree->text = text;
    tree->type = NK_TREE_NODE;

    if (parent) {
        auto node = parent->GetComponent<NodeComponent>();
        if (!node) {
            node = World::Instance()->CreateComponent<NodeComponent>();
            parent->SetComponent(node);
        }
        node->Attach(entity);
    }
    return entity;
}

}