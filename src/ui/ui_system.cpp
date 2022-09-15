#include "engine/ui/ui_system.hpp"

namespace engine {

std::optional<bool> UISystem::BeginContainer(Entity* entity) {
    nk_context* ctx = UI::NkContext();

    if (nk_window_is_any_hovered(ctx)) {
        Event::GetDispatcher().EventedTriggedOnUI();
    }
    if (auto window = entity->GetComponent<UIWindow>(); window) {
        struct nk_rect rect{window->rect.position.x, window->rect.position.y, window->rect.size.w, window->rect.size.h};
        return nk_begin(UI::NkContext(), window->title.c_str(), rect, window->flags);
    } else if (auto layout = entity->GetComponent<UIStaticRowLayout>(); layout) {
        nk_layout_row_static(ctx, layout->height, layout->itemWidth, layout->cols);
        return std::nullopt;
    } else if (auto layout = entity->GetComponent<UIDynamicRowLayout>(); layout) {
        nk_layout_row_dynamic(ctx, layout->height, layout->cols);
        return std::nullopt;
    } else if (auto tree = entity->GetComponent<UITree>(); tree) {
        return nk_tree_push_id(ctx, tree->type, tree->text.c_str(), tree->state, tree->TreeID());
    }
    return std::nullopt;
}

void UISystem::EndContainer(Entity* entity) {
    nk_context* ctx = UI::NkContext();

    if (auto tree = entity->GetComponent<UITree>(); tree) {
        nk_tree_pop(ctx);
    } else {
        nk_end(ctx);
    }
}

void UISystem::Update(Entity* entity) {
    nk_context* ctx = UI::NkContext();

    if (auto button = entity->GetComponent<UIButton>(); button) {
        if (nk_button_label(UI::NkContext(), button->text.c_str())) {
            if (button->onClick) button->onClick(entity, button->param);
        }
    } else if (auto checkbox = entity->GetComponent<UICheckbox>(); checkbox) {
        if (nk_option_label(ctx, checkbox->text.c_str(), checkbox->isSelected)) {
            if (checkbox->callback) checkbox->callback(entity);
        }
    } else if (auto label = entity->GetComponent<UILabel>(); label) {
        nk_label(ctx, label->text.c_str(), label->align);
    }
}

}
