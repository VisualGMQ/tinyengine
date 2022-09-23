#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/dllexport.hpp"

namespace engine {

class Entity;

using ComponentID = unsigned int;

class DLLEXPORT Component {
public:
    friend class Entity;
    friend class World;

    Component(ComponentID id): id_(id) {}
    virtual ~Component() = default;

    Component(const Component&) = default;
    Component& operator=(const Component&) = delete;

    virtual void Reset() {}
    Entity* Parent() const { return parent_; }

    unsigned int ID() const { return id_; }

private:
    ComponentID id_;
    Entity* parent_ = nullptr;
};

class ComponentIDHelper final {
public:
    template <typename T>
    DLLEXPORT static unsigned int GetID() {
        static_assert(std::is_base_of_v<Component, T> && !std::is_same_v<Component, T>);
        static unsigned int id = curIdx_++;
        return id;
    }

private:
    static unsigned int curIdx_;
};


}
