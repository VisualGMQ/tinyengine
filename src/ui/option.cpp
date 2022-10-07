#include "engine/ui/option.hpp"

namespace engine {

void UIOption::Reset() {
    Component::Reset();
    text = "checkbox";
    isSelected = false;
    callback = nullptr;
}

Entity* CreateUIOption(const std::string& name, const std::string& text, UIOption::CallbackType callback, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity<UIOption, NodeComponent>(name);
    auto option = entity->GetComponent<UIOption>();
    option->text = text;
    option->callback = callback;

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