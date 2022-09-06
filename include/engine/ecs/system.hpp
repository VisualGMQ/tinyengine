#pragma once

namespace engine {

class World;
class Entity;

class System {
public:
    System(World* world): world_(world) {}
    virtual ~System() = default;

    virtual void Update(Entity*) = 0;

    World* World() const { return world_; }

private:
    class World* world_;
};

}