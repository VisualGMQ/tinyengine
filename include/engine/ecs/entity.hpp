#pragma once

#include "engine/ecs/component.hpp"

namespace engine {

class Entity final {
public:
    Entity(const std::string& name): name_(name) {}

    template <typename T>
    void SetComponent(T*);

    template <typename T>
    T* GetComponent();

    template <typename T>
    void RemoveComponent();

    const std::string& Name() const { return name_; }

    inline void Update() {
        for (auto& [key, value] : components_) {
            value->OnUpdate();
        }
    }

private:
    std::unordered_map<unsigned int, Component*> components_;

    std::string name_;
};


template <typename T>
void Entity::SetComponent(T* comp) {
    static_assert(std::is_base_of_v<Component, T> && !std::is_same_v<Component, T>);
    unsigned int id = ComponentIDHelper::GetID<T>();
    auto it = components_.find(id);
    if (it != components_.end()) {
        Logw("entity %s already has component %s", Name().c_str(), comp->Name().c_str());
    }
    components_[id] = comp;
    comp->OnInit();
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
    auto it = components_.find(ComponentIDHelper::GetID<T>());
    if (it != components_.end()) {
        it->second->OnQuit();
        ComponentFactory::Remove<MyComponent>((T*)it->second);
        components_.erase(it);
    }
}

inline std::shared_ptr<Entity> CreateEntity(const std::string& name) {
    return std::make_shared<Entity>(name);
}

}