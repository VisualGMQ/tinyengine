#pragma once

#include "engine/ecs/component.hpp"
#include "engine/ecs/world.hpp"

namespace engine {

using EntityID = unsigned int;

class Entity final {
public:
    friend class World;

    Entity(World* world, EntityID id, const std::string& name): world_(world), id_(id), name_(name) {}

    template <typename T>
    void SetComponent(T*);

    template <typename T>
    T* GetComponent();

    template <typename T>
    void RemoveComponent();

    const std::string& Name() const { return name_; }

    EntityID ID() const { return id_; }
    World* World() const { return world_; }

private:
    std::unordered_map<unsigned int, Component*> components_;
    class World* world_;

    EntityID id_;
    std::string name_;
    bool shouldBeCleanUp_ = false;
};


template <typename T>
void Entity::SetComponent(T* comp) {
    static_assert(std::is_base_of_v<Component, T> && !std::is_same_v<Component, T>);
    if (!comp) {
        Logw("component is nullptr");
        return;
    }
    unsigned int id = ComponentIDHelper::GetID<T>();
    auto it = components_.find(id);
    if (it != components_.end()) {
        Logw("entity %s already has component %s, set failed", Name().c_str(), it->second->Name().c_str());
        return;
    }
    components_[id] = comp;
    comp->OnInit();
    comp->parent_ = this;
}

template <typename T>
T* Entity::GetComponent() {
    static_assert(std::is_base_of_v<Component, T> && !std::is_same_v<Component, T>);
    auto it = components_.find(ComponentIDHelper::GetID<T>());
    if (it == components_.end()) {
        return nullptr;
    } else {
        return static_cast<T*>(it->second);
    }
}

template <typename T>
void Entity::RemoveComponent() {
    static_assert(std::is_base_of_v<Component, T> && !std::is_same_v<Component, T>);

    unsigned int id = ComponentIDHelper::GetID<T>();
    auto component = components_[id];
    component->OnQuit();
    components_.erase(id);
    world_->RemoveComponent(component);
}

}