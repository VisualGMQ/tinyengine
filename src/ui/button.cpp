#include "engine/ui/button.hpp"

namespace engine {

void UIButton::Reset() {
    Component::Reset();
    text = "button";
    onClick = nullptr;
    param = nullptr;
}

Entity* CreateUIButton(const std::string& name, const std::string& text, UIButton::CallbackType callback, void* param, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity<UIButton, NodeComponent>(name);
    auto button = entity->GetComponent<UIButton>();
    button->text = text;
    button->onClick = callback;
    button->param = param;

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