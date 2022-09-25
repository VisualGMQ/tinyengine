#include "engine/ecs/system.hpp"
#include "engine/ecs/world.hpp"

namespace engine {

class RenderSystem: public System {
public:
    RenderSystem(engine::World* world): System(world) {}
    void Update(Entity*) override {}
    Mat4 Update(Entity*, const Mat4&);
};

}