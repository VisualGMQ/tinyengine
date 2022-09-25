#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"
#include "nuklear.h"

namespace engine {

class DLLEXPORT UICheckbox: public Component {
public:
    using CallbackType = std::function<void(Entity*, UICheckbox*)>;

    UICheckbox(ComponentID id): Component(id) { Reset(); }
    void Reset() override;

    nk_bool isSelected;
    std::string text;
    CallbackType callback;
};

Entity* CreateUICheckbox(const std::string& name, const std::string& text, UICheckbox::CallbackType, Entity* parent);

}