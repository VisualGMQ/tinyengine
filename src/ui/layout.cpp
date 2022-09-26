#include "engine/ui/layout.hpp"

namespace engine {

void UIStaticRowLayout::Reset() {
    Component::Reset();
    height = 30;
    itemWidth = 50;
    cols = 1;
}

void UIDynamicRowLayout::Reset() {
    height = 30;
    cols = 1;
}

void UIRowLayout::Reset() {
    format = NK_DYNAMIC;
    height = 20;
    ratio.clear();
    ratio.push_back(1);
}

void UIFreeLayout::Reset() {
    format = NK_DYNAMIC;
    height = 20;
    widgetCount = 1;
}

Entity* CreateUIStaticRowLayout(const std::string& name, float height, int widgetWidth, int cols, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto layout = World::Instance()->CreateComponent<UIStaticRowLayout>();
    layout->height = height;
    layout->itemWidth = widgetWidth;
    layout->cols = cols;
    entity->SetComponent(layout);

    if (parent) {
        auto node = parent->GetComponent<NodeComponent>();
        if (node) {
            node->Attach(entity);
        }
    }
    return entity;
}

Entity* CreateUIDynamicRowLayout(const std::string& name, float height, int cols, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto layout = World::Instance()->CreateComponent<UIDynamicRowLayout>();
    layout->height = height;
    layout->cols = cols;
    entity->SetComponent(layout);

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

Entity* CreateUIRowLayout(const std::string& name, nk_layout_format format, float height, const std::vector<float> ratio, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto layout = World::Instance()->CreateComponent<UIRowLayout>();
    layout->height = height;
    layout->ratio = ratio;
    layout->format = format;
    entity->SetComponent(layout);

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

Entity* CreateUIFreeLayout(const std::string& name, nk_layout_format format, float height, int widgetCount, Entity* parent) {
    Entity* entity = World::Instance()->CreateEntity(name);
    auto layout = World::Instance()->CreateComponent<UIFreeLayout>();
    layout->height = height;
    layout->widgetCount = widgetCount;
    layout->format = format;
    entity->SetComponent(layout);

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
