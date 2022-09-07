#pragma once

#include "engine/ecs/component.hpp"
#include "nuklear/nuklear.h"

namespace engine {

class UIStaticRowLayout final: public Component {
public:
    UIStaticRowLayout(ComponentID id, const std::string& name): Component(id, name) {}
    void Reset() override;

    float height;
    int itemWidth;
    int cols;
};

class UIDynamicRowLayout final: public Component {
public:
    UIDynamicRowLayout(ComponentID id, const std::string& name): Component(id, name) {}
    void Reset() override;

    float height;
    int cols;
};

/*
class UIRowLayout final: public Component {
public:
    UIRowLayout(ComponentID id, const std::string& name): Component(id, name) {}
    void Reset() override;

    nk_layout_format format;
    float height;
    int col;
    std::vector<float> ratio;
};
*/

}