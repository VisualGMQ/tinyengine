#include "engine/ui/checkbox.hpp"

namespace engine {

void UICheckbox::Reset() {
    Component::Reset();
    text = "checkbox";
    isSelected = false;
    callback = nullptr;
}

Entity* CreateUICheckbox(const std::string& name, const std::string& text, UICheckbox::CallbackType callback, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity<UICheckbox, NodeComponent>(name);
    auto checkbox = entity->GetComponent<UICheckbox>();
    checkbox->text = text;
    checkbox->callback = callback;

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