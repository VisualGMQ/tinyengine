#include "engine/ui/text.hpp"

namespace engine {

void UIText::Reset() {
    Component::Reset();
    text = "text";
    flags = 0;
}

Entity* CreateUIText(const std::string& name, const std::string& text, int flags, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity<UIText, NodeComponent>(name);
    auto uitext = entity->GetComponent<UIText>();
    uitext->text = text;
    uitext->flags = flags;

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