#include "engine/ecs/system.hpp"
#include "engine/ecs/world.hpp"

namespace engine {

class RenderSystem: public EntityUpdateSystem {
public:
    RenderSystem(engine::World* world): EntityUpdateSystem(world) {}
    void Update(Entity*) override;
};

}