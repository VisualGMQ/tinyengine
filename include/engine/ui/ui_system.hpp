#pragma once

#include "engine/ecs/system.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/ecs/world.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/ui/button.hpp"
#include "engine/input/input.hpp"

namespace engine {

class UISystem final: public System {
public:
    UISystem(class World* world): System(world) {}
    void Update(Entity*) override;

private:
    void drawButton(RectTransform*, ButtonComponent*);
};

}
