#pragma once

#include "engine/core/dllexport.hpp"
#include "engine/ecs/world.hpp"
#include "engine/ecs/component.hpp"

namespace engine {

void SetNodeParent(Entity* parent, Entity* child);

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
        parentNode_ = nullptr;
    }

    void SetParentNode(Entity* parent) { parentNode_ = parent; }
    Entity* GetParentNode() const { return parentNode_; }

    void Attach(Entity* entity) {
        children.push_back(entity);
        SetNodeParent(Parent(), entity);
    }

    std::vector<Entity*> children;

private:
    Entity* parentNode_ = nullptr;
};

class Node2DComponent: public NodeComponent {
public:
    Node2DComponent(ComponentID id): NodeComponent(id) { Reset(); }
    void Reset() override;

    bool TryUpdateLocalTransform();
    const Mat4& GetLocalTransform() const { return localTransform_; }
    const Mat4& GetGlobalTransform() const { return globalTransform_; }

    void UpdateGlobalTransform(const Mat4& transform) { globalTransform_ = transform; }
    void DetectDirt();

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

    Mat4 globalTransform_;
    Mat4 localTransform_;
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
};

class Node3DRoot: public Component {
public:
    Node3DRoot(ComponentID id): Component(id) {}
};

class NodeUIRoot final: public Component {
public:
    NodeUIRoot(ComponentID id): Component(id) {}
};

}