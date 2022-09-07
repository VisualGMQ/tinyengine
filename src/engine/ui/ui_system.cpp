#include "engine/ui/ui_system.hpp"

namespace engine {

std::optional<bool> UISystem::BeginContainer(Entity* entity) {
    if (auto window = entity->GetComponent<UIWindow>(); window) {
        struct nk_rect rect{window->rect.position.x, window->rect.position.y, window->rect.size.w, window->rect.size.h};
        return nk_begin(UI::NkContext(), window->title.c_str(), rect, window->flags);
    }
    return std::nullopt;
}

void UISystem::EndContainer(Entity* entity) {
    if (auto window = entity->GetComponent<UIWindow>(); window) {
        nk_end(UI::NkContext());
    }
}

void UISystem::Update(Entity* entity) {
    if (auto button = entity->GetComponent<UIButton>(); button) {
        if (nk_button_label(UI::NkContext(), button->text.c_str())) {
            if (button->onClick) {
                button->onClick(entity);
            }
        }
    }
}

}
