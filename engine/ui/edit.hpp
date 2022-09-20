#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"
#include "nuklear.h"

namespace engine {

class UIEdit: public Component {
public:
    UIEdit(ComponentID id) : Component(id) { Reset(); }

    void Reset() override;

    int options;
    int maxLength;
    int len;
    nk_plugin_filter filter;
    char buffer[1024];
};

Entity* CreateUIEdit(const std::string& name, int options = NK_EDIT_FIELD, int maxLength = 1023, nk_plugin_filter filter = nullptr, Entity* parent = nullptr);

}