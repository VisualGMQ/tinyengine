#include "engine/ui/edit.hpp"

namespace engine {

void UIEdit::Reset() {
    Component::Reset();
    options = NK_EDIT_FIELD;
    len = 0;
    maxLength = 1023;
    filter = nullptr;
    onEnterKeyPress = nullptr;
    memset(buffer, 0, sizeof(buffer));
}

Entity* CreateUIEdit(const std::string& name, int options, int maxLength, nk_plugin_filter filter, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity<UIEdit, NodeComponent>(name);
    auto edit = entity->GetComponent<UIEdit>();
    edit->options = options;
    edit->len = 0;
    edit->maxLength = maxLength;
    edit->filter = filter;

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
