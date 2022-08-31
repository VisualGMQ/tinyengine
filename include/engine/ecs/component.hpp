#pragma once

#include "engine/core/pch.hpp"

namespace engine {

class Component {
public:
    friend class Entity;
    Component(const std::string& name): name_(name) {}
    virtual ~Component() = default;

    const std::string& Name() const { return name_; }
    virtual void OnInit() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnQuit() = 0;
    Entity* Parent() { return parent_; }

private:
    std::string name_;
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

class ComponentFactory final {
public:
    template <typename T>
    static T* Create(const std::string& name) {
        return operatorComponent<T>(Operator::Create, name, nullptr);
    }

    template <typename T>
    static void Remove(T* component) {
        operatorComponent<T>(Operator::Remove, "", component);
    }

private:
    enum class Operator {
        Create,
        Remove
    };

    template <typename T>
    static T* operatorComponent(Operator op, const std::string& name, T* removeComponent) {
        static_assert(std::is_base_of_v<Component, T> && !std::is_same_v<Component, T>);

        static std::stack<std::unique_ptr<T>> trashs;
        static std::vector<std::unique_ptr<T>> components;

        if (op == Operator::Create) {
            return create(trashs, components, name);
        } else if (op == Operator::Remove) {
            remove(trashs, components, removeComponent);
            return nullptr;
        }
        return nullptr;
    }

    template <typename T>
    static T* create(std::stack<std::unique_ptr<T>>& trashs, std::vector<std::unique_ptr<T>>& components, const std::string& name) {
        if (trashs.empty()) {
            components.push_back(std::make_unique<T>(name));
            return components.back().get();
        } else {
            auto& component = trashs.top();
            components.push_back(std::move(component));
            trashs.pop();
            return components.back().get();
        }
    }

    template <typename T>
    static void remove(std::stack<std::unique_ptr<T>>& trashs, std::vector<std::unique_ptr<T>>& components, T* component) {
        auto it = components.begin();
        while (it != components.end() && it->get() != component) {
            it ++;
        }
        if (it != components.end()) {
            trashs.push(std::move(*it));
            components.erase(it);
        }
    }
};

}