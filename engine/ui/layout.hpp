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

class DLLEXPORT UIRowLayout final: public Component {
public:
    UIRowLayout(ComponentID id) : Component(id) { Reset(); }
    void Reset() override;

    nk_layout_format format;
    float height;
    std::vector<float> ratio;
};

class DLLEXPORT UIFreeLayout final: public Component {
public:
    UIFreeLayout(ComponentID id): Component(id) { Reset(); }
    void Reset() override;

    nk_layout_format format;
    float height;
    int widgetCount;
};

Entity* CreateUIStaticRowLayout(const std::string& name, float height, int widgetWidth, int cols, Entity* parent);
Entity* CreateUIDynamicRowLayout(const std::string& name, float height, int cols, Entity* parent);
Entity* CreateUIRowLayout(const std::string& name, nk_layout_format, float height, const std::vector<float> ratio, Entity* parent);
Entity* CreateUIFreeLayout(const std::string& name, nk_layout_format, float height, int widgetCount, Entity* parent);

}