#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"
#include "nuklear.h"

namespace engine {

class DLLEXPORT UIStaticRowLayout final: public Component {
public:
    UIStaticRowLayout(ComponentID id) : Component(id) { Reset(); }
    void Reset() override;

    float height;
    int itemWidth;
    int cols;
};

class DLLEXPORT UIDynamicRowLayout final: public Component {
public:
    UIDynamicRowLayout(ComponentID id) : Component(id) { Reset(); }
    void Reset() override;

    float height;
    int cols;
};

Entity* CreateUIStaticRowLayout(const std::string& name, float height, int widgetWidth, int cols, Entity* parent);
Entity* CreateUIDynamicRowLayout(const std::string& name, float height, int cols, Entity* parent);

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