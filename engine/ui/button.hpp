#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class DLLEXPORT UIButton: public Component {
public:
    using CallbackType = std::function<void(Entity*, void*)>;
    UIButton(ComponentID id, const std::string& name): Component(id, name) {}

    void Reset() override;

    std::string text;
    CallbackType onClick;
    void* param;
};

}