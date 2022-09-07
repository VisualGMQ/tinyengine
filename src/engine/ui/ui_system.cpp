#include "engine/ui/ui_system.hpp"

namespace engine {

std::optional<bool> UISystem::BeginContainer(Entity* entity) {
    nk_context* ctx = UI::NkContext();

    if (auto window = entity->GetComponent<UIWindow>(); window) {
        struct nk_rect rect{window->rect.position.x, window->rect.position.y, window->rect.size.w, window->rect.size.h};
        return nk_begin(UI::NkContext(), window->title.c_str(), rect, window->flags);
    } else if (auto layout = entity->GetComponent<UIStaticRowLayout>(); layout) {
        nk_layout_row_static(ctx, layout->height, layout->itemWidth, layout->cols);
        return std::nullopt;
    } else if (auto layout = entity->GetComponent<UIDynamicRowLayout>(); layout) {
        nk_layout_row_dynamic(ctx, layout->height, layout->cols);
        return std::nullopt;
    }
    return std::nullopt;
}

void UISystem::EndContainer(Entity* entity) {
    nk_end(UI::NkContext());
}

void UISystem::Update(Entity* entity) {
    nk_context* ctx = UI::NkContext();
    if (auto button = entity->GetComponent<UIButton>(); button) {
        if (nk_button_label(UI::NkContext(), button->text.c_str())) {
            if (button->onClick) button->onClick(entity);
        }
    } else if (auto checkbox = entity->GetComponent<UICheckbox>(); checkbox) {
        if (nk_option_label(ctx, checkbox->text.c_str(), checkbox->isSelected)) {
            if (checkbox->callback) checkbox->callback(entity);
        }
    }
}

}
