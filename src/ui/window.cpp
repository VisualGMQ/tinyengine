#include "engine/ui/window.hpp"

namespace engine {

void UIWindow::Reset() {
    Component::Reset();
    title.clear();
    flags = 0;
    rect.position.Set(0, 0);
    rect.size.Set(200, 200);
}

Entity* CreateUIWindow(const std::string& name, const std::string& title, nk_flags flags, const Rect& rect) {
    Entity* entity = World::Instance()->CreateEntity<UIWindow, NodeComponent>(name);
    auto window = entity->GetComponent<UIWindow>();
    window->title = title;
    window->flags = flags;
    window->rect = rect;

    return entity;
}

}