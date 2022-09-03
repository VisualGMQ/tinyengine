#pragma once

#include "engine/ui/recttransform.hpp"
#include "engine/ui/ui.hpp"
#include "engine/renderer/image.hpp"

namespace engine {

class ButtonComponent: public UIBase {
public:
    using Callback = std::function<void(ButtonComponent*)>;

    ButtonComponent(ComponentID id, const std::string& name): UIBase(id, name) {}

    void OnInit() override;
    void OnQuit() override {}

    std::string text;
    std::shared_ptr<Image> image;
    Color borderColor;
    Color bgColor;
    Callback clickCb;
    Callback motionCb;
    // Color frontColor;
};

}
