#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"

namespace engine {

class DLLEXPORT UIOption: public Component {
public:
    using CallbackType = std::function<void(Entity*, UIOption*)>;

    UIOption(ComponentID id): Component(id) { Reset(); }
    void Reset() override;

    bool isSelected;
    std::string text;
    CallbackType callback;
};

Entity* CreateUIOption(const std::string& name, const std::string& text, UIOption::CallbackType, Entity* parent);

}