#pragma once

#include "engine/ecs/component.hpp"
#include "nuklear.h"

namespace engine {

class UILabel: public Component {
public:
    UILabel(ComponentID id): Component(id) {}
    void Reset() override;

    std::string text;
    nk_flags align;
};

}