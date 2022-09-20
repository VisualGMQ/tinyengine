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
    } else if (auto group = entity->GetComponent<UIGroup>(); group) {
        return nk_group_begin(ctx, group->title.c_str(), group->options);
    }
    return std::nullopt;
}

void UISystem::EndContainer(Entity* entity, bool isShowed) {
    nk_context* ctx = UI::NkContext();

    if (auto tree = entity->GetComponent<UITree>(); tree) {
        if (isShowed) {
            nk_tree_pop(ctx);
        }
    } else if (auto group = entity->GetComponent<UIGroup>(); group) {
        if (isShowed) {
            nk_group_end(ctx);
        }
    } else {
        nk_end(ctx);
    }
}

void UISystem::Update(Entity* entity) {
    nk_context* ctx = UI::NkContext();

    if (auto button = entity->GetComponent<UIButton>(); button) {
        if (nk_button_label(ctx, button->text.c_str())) {
            if (button->onClick) button->onClick(entity, button, button->param);
        }
    } else if (auto checkbox = entity->GetComponent<UICheckbox>(); checkbox) {
        if (nk_checkbox_label(ctx, checkbox->text.c_str(), &checkbox->isSelected)) {
            if (checkbox->callback) checkbox->callback(entity, checkbox);
        }
    } else if (auto option = entity->GetComponent<UIOption>(); option) {
        if (nk_option_label(ctx, option->text.c_str(), option->isSelected)) {
            if (option->callback) option->callback(entity, option);
        }
    } else if (auto label = entity->GetComponent<UILabel>(); label) {
        nk_label(ctx, label->text.c_str(), label->align);
    } else if (auto edit = entity->GetComponent<UIEdit>(); edit) {
        nk_edit_string(ctx, edit->options, edit->buffer, &edit->len, edit->maxLength, edit->filter);
    } else if (auto property = entity->GetComponent<UIProperty>(); property) {
        property->oldValue = property->Value();
        if (property->type == UIProperty::Int) {
            nk_property_int(ctx, property->text.c_str(), property->min, &property->ivalue, property->max, property->incStep, property->incPerPixel);
        } else if (property->type == UIProperty::Float) {
            nk_property_float(ctx, property->text.c_str(), property->min, &property->fvalue, property->max, property->incStep, property->incPerPixel);
        } else if (property->type == UIProperty::Double) {
            nk_property_double(ctx, property->text.c_str(), property->min, &property->dvalue, property->max, property->incStep, property->incPerPixel);
        }
        if (property->oldValue != property->Value() && property->callback) {
            property->callback(entity, property);
        }
    }
}

}
