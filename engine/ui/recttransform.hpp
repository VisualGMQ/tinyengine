#pragma once

#include "engine/ecs/component.hpp"
#include "engine/core/vmath.hpp"

namespace engine {

class DLLEXPORT RectTransform final: public Component {
public:
    RectTransform(ComponentID id): Component(id) {}
    void OnInit() override {
        anchor.Set(0, 0);
        size(0, 0);
        position(0, 0);
    } 
    void OnQuit() override{}

    Vec2 anchor;
    Size size;
    Vec2 position;
};

}
