#include "engine/ui/group.hpp"

namespace engine {

void UIGroup::Reset() {
    options = NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR;
}

Entity* CreateUIGroup(const std::string& name, const std::string& title, nk_flags options, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto group = World::Instance()->CreateComponent<UIGroup>();
    group->options = options;
    group->title = title;
    entity->SetComponent(group);

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