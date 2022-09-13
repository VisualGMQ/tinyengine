#pragma once

#include "engine/ecs/component.hpp"
#include "nuklear.h"

namespace engine {

class UILabel: public Component {
public:
    UILabel(ComponentID id, const std::string& name): Component(id, name) {}
    void Reset() override;

    std::string text;
    nk_flags align;
};

}