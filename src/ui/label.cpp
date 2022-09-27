#include "engine/ui/label.hpp"

namespace engine {

void UILabel::Reset() {
    Component::Reset();
    text = "label";
    align = NK_TEXT_ALIGN_LEFT;
    wrap = false;
}

Entity* CreateUILabel(const std::string& name, const std::string& text, nk_flags align, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto label = World::Instance()->CreateComponent<UILabel>();
    label->text = text;
    label->align = align;
    entity->SetComponent(label);

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
