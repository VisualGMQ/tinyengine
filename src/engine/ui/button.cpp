#include "engine/ui/button.hpp"

namespace engine {

void ButtonComponent::OnInit() {
    UIBase::OnInit();

    text.clear();
    image.reset();
    borderColor.Set(0, 0, 0);
    bgColor.Set(1, 1, 1);
    clickCb = nullptr;
    motionCb = nullptr;
}

}
