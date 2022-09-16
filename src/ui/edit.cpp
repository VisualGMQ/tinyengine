#include "engine/ui/edit.hpp"

namespace engine {

void UIEdit::Reset() {
    options = NK_EDIT_FIELD;
    len = 0;
    maxLength = 1023;
    filter = nullptr;
}

Entity* CreateUIEdit(const std::string& name, int options, int maxLength, nk_plugin_filter filter, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto edit = World::Instance()->CreateComponent<UIEdit>();
    edit->options = options;
    edit->len = 0;
    edit->maxLength = maxLength;
    edit->filter = filter;
    entity->SetComponent(edit);

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