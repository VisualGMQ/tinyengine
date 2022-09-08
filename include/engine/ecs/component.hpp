#pragma once

#include "engine/core/pch.hpp"

namespace engine {

class Entity;

using ComponentID = unsigned int;

class DLLEXPORT Component {
public:
    friend class Entity;
    friend class World;

    Component(ComponentID id, const std::string& name): id_(id), name_(name) {}
    virtual ~Component() = default;

    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    const std::string& Name() const { return name_; }
    virtual void Reset() {}
    Entity* Parent() const { return parent_; }

    unsigned int ID() const { return id_; }

private:
    std::string name_;
    ComponentID id_;
    Entity* parent_ = nullptr;
};

class DLLEXPORT ComponentIDHelper final {
public:
    template <typename T>
    static unsigned int GetID() {
        static_assert(std::is_base_of_v<Component, T> && !std::is_same_v<Component, T>);
        static unsigned int id = curIdx_++;
        return id;
    }

private:
    static unsigned int curIdx_;
};


}
