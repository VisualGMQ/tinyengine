#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class DLLEXPORT UIButton: public Component {
public:
    using CallbackType = std::function<void(Entity*, void*)>;
    UIButton(ComponentID id): Component(id) {}

    void Reset() override;

    std::string text;
    CallbackType onClick;
    void* param;
};

}