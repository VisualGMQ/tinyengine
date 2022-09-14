#pragma once

#include "engine/ecs/component.hpp"
#include "nuklear.h"

namespace engine {

class DLLEXPORT UIStaticRowLayout final: public Component {
public:
    UIStaticRowLayout(ComponentID id): Component(id) {}
    void Reset() override;

    float height;
    int itemWidth;
    int cols;
};

class DLLEXPORT UIDynamicRowLayout final: public Component {
public:
    UIDynamicRowLayout(ComponentID id): Component(id) {}
    void Reset() override;

    float height;
    int cols;
};

/*
class UIRowLayout final: public Component {
public:
    UIRowLayout(ComponentID id): Component(id) {}
    void Reset() override;

    nk_layout_format format;
    float height;
    int col;
    std::vector<float> ratio;
};
*/

}