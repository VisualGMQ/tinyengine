#pragma once

#include "engine/core/pch.hpp"

namespace engine {

class Entity;

class Component {
public:
    friend class Entity;
    friend class World;

    Component(unsigned int id, const std::string& name): id_(id), name_(name) {}
    virtual ~Component() = default;

    const std::string& Name() const { return name_; }
    virtual void OnInit() = 0;
    virtual void OnQuit() = 0;
    Entity* Parent() const { return parent_; }

    unsigned int ID() const { return id_; }

private:
    std::string name_;
    unsigned int id_;
    Entity* parent_ = nullptr;
};

class ComponentIDHelper final {
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