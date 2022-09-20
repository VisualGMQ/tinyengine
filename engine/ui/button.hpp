#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"

namespace engine {

class DLLEXPORT UIButton: public Component {
public:
    using CallbackType = std::function<void(Entity*, UIButton*, void*)>;
    UIButton(ComponentID id) : Component(id) { Reset(); }

    void Reset() override;

    std::string text;
    CallbackType onClick;
    void* param;
};

Entity* CreateUIButton(const std::string& name, const std::string& text, UIButton::CallbackType callback, void* param, Entity* parent);

}