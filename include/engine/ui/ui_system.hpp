#pragma once

#include "engine/ecs/system.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/ecs/world.hpp"
#include "engine/ecs/entity.hpp"
#include "engine/input/input.hpp"
#include "engine/ui/ui.hpp"
#include "engine/ui/window.hpp"
#include "engine/ui/button.hpp"
#include "engine/ui/checkbox.hpp"
#include "engine/ui/layout.hpp"

namespace engine {

class DLLEXPORT UISystem final: public System {
public:
    UISystem(class World* world): System(world) {}

    std::optional<bool> BeginContainer(Entity*);
    void EndContainer(Entity*);
    void Update(Entity*) override;
};

}
