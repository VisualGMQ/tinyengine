#include "engine/ui/group.hpp"

namespace engine {

void UIGroup::Reset() {
    Component::Reset();
    options = NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR;
}

Entity* CreateUIGroup(const std::string& name, const std::string& title, nk_flags options, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity<UIGroup, NodeComponent>(name);
    auto group = entity->GetComponent<UIGroup>();
    group->options = options;
    group->title = title;

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