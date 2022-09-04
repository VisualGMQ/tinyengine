#include "engine/ui/ui_system.hpp"

namespace engine {

void UISystem::Update() {
    Renderer::Begin2D();
    Renderer::SetDrawColor(Color(1, 1, 1));
    for (auto& entity : World()->Entities()) {
        auto button = entity->GetComponent<ButtonComponent>();
        auto transform = entity->GetComponent<RectTransform>();
        if (button && transform) {
            drawButton(transform, button);
        }
    }
}

void UISystem::drawButton(RectTransform* transform, ButtonComponent* button) {
    Rect rect;
    if (transform) {
        rect.position = transform->position - MulEach(transform->anchor, transform->size);
        rect.size = transform->size;
    }

    if (button->shouldRaycast && IsPointInRect(Input::MousePoition(), rect)) {
        if (button->clickCb && Input::IsButtonPressed(MouseButton::Left)) {
            button->clickCb(button);
        }
        if (Input::MouseRelative() != Vec2(0, 0)) {
            if (button->motionCb) {
                button->motionCb(button);
            }
        }
    }

    if (button->image) {
        button->image->SetPosition(rect.position);
        button->image->SetSize(rect.size);
        button->image->Draw();
    } else {
        Renderer::SetDrawColor(button->bgColor);
        Renderer::FillRect(rect);
    }
    Renderer::SetDrawColor(button->borderColor);
    Renderer::DrawRect(rect);
}

}
