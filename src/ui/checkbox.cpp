#include "engine/ui/checkbox.hpp"

namespace engine {

void UICheckbox::Reset() {
    text = "checkbox";
    isSelected = true;
    callback = nullptr;
}

Entity* CreateUICheckbox(const std::string& name, const std::string& text, UICheckbox::CallbackType callback, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto checkbox = World::Instance()->CreateComponent<UICheckbox>();
    checkbox->text = text;
    checkbox->callback = callback;
    entity->SetComponent(checkbox);

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