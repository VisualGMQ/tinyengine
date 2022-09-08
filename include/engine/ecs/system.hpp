#pragma once

namespace engine {

class World;
class Entity;

class DLLEXPORT System {
public:
    System(World* world): world_(world) {}
    System(const System&) = delete;
    System& operator=(const System&) = delete;

    virtual ~System() = default;

    virtual void Update(Entity*) = 0;

    World* World() const { return world_; }

private:
    class World* world_;
};

}