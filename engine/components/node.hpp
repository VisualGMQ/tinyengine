#pragma once

#include "engine/ecs/component.hpp"
#include "engine/core/dllexport.hpp"
#include "engine/ecs/world.hpp"

namespace engine {

class DLLEXPORT NodeComponent: public Component {
public:
    NodeComponent(ComponentID id): Component(id) { Reset(); }
    virtual ~NodeComponent() = default;

    virtual void Reset() override {
        Component::Reset();
        for (auto& child : children) {
            World::Instance()->DestroyEntity(child);
        }
        children.clear();
    }

    void Attach(Entity* entity) { children.push_back(entity); }

    std::vector<Entity*> children;
};

class Node2DComponent: public NodeComponent {
public:
    Node2DComponent(ComponentID id): NodeComponent(id) { Reset(); }
    void Reset() override;

    void DetectDirt();
    bool TryUpdateTransform();
    const Mat4& GetTransform() const { return transform_; }

    float rotation;
    Vec2 scale;
    Vec2 position;
    float zIndex;

private:
    enum Dirt {
        None = 0,
        Translate = 0x01,
        Scale = 0x02,
        Rotate = 0x04,
    };
    uint32_t dirt_ = None;

    float oldRotation_;
    Vec2 oldScale_;
    Vec2 oldPosition_;
    float oldZIndex_;

    Mat4 transform_;
    Mat4 rotationMat_;
    Mat4 translateMat_;
    Mat4 scaleMat_;
    void tryCalcScaleMat();
    void tryCalcTranslateMat();
    void tryCalcRotateMat();
};

class Node2DRoot: public Component {
public:
    Node2DRoot(ComponentID id): Component(id) {}
    void Reset() override { Component::Reset(); }
};

class Node3DRoot: public Component {
public:
    Node3DRoot(ComponentID id): Component(id) {}
    void Reset() override { Component::Reset(); }
};

class NodeUIRoot final: public Component {
public:
    NodeUIRoot(ComponentID id): Component(id) {}
    void Reset() override { Component::Reset(); }
};

}