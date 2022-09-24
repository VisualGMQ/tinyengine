#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"
#include "engine/components/node.hpp"
#include "engine/renderer/texture.hpp"
#include "nuklear.h"

namespace engine {

class UIImage: public Component {
public:
    UIImage(ComponentID id) : Component(id) { Reset(); }
    void Reset() override;

    Texture* texture;
    int w;
    int h;
    Rect region;
    Color color;
};

Entity* CreateUIImage(const std::string& name, Texture*, int w, int h, const Rect& region, const Color& color, Entity* parent);

}