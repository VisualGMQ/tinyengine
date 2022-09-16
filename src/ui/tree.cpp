#include "engine/ui/tree.hpp"

namespace engine {

int UITree::curId_ = 0;

void UITree::Reset() {
    type = NK_TREE_TAB;
    state = NK_MINIMIZED;
    text = "tree node";
}

Entity* CreateUITreeTab(const std::string& name, const std::string& text, nk_collapse_states state, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto tree = World::Instance()->CreateComponent<UITree>();
    tree->state = state;
    tree->text = text;
    tree->type = NK_TREE_TAB;
    entity->SetComponent(tree);

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
    Entity* entity = World::Instance()->CreateEntity(name);
    auto tree = World::Instance()->CreateComponent<UITree>();
    tree->state = state;
    tree->text = text;
    tree->type = NK_TREE_NODE;
    entity->SetComponent(tree);

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