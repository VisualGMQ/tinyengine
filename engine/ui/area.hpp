#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class UIAreaComponent: public Component {
public:
    UIAreaComponent(ComponentID id): Component(id) { Reset(); }
    void Reset() override {
        area.position.Set(0, 0);
        area.size.Set(20, 20);
    }

    Rect area;
};

}