#include "engine/ui/option.hpp"

namespace engine {

void UIOption::Reset() {
    text = "checkbox";
    isSelected = false;
    callback = nullptr;
}

Entity* CreateUIOption(const std::string& name, const std::string& text, UIOption::CallbackType callback, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto option = World::Instance()->CreateComponent<UIOption>();
    option->text = text;
    option->callback = callback;
    entity->SetComponent(option);

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