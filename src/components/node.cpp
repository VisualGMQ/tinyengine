#include "engine/components/node.hpp"

namespace engine {

void SetNodeParent(Entity* parent, Entity* child) {
    if (auto node = child->GetComponent<NodeComponent>(); node) {
        node->SetParentNode(parent);
    } else if (auto node = child->GetComponent<Node2DComponent>(); node) {
        node->SetParentNode(parent);
    } else {
        Loge("entity {} don't has any node component", child->Name());
    }
}

void Node2DComponent::Reset() {
    NodeComponent::Reset();

    position.Set(0, 0);
    scale.Set(1, 1);
    rotation = 0;

    zIndex = 0;

    localTransform_ = IdentityMat4;
    globalTransform_ = IdentityMat4;
    rotationMat_ = IdentityMat4;
    translateMat_ = IdentityMat4;
    scaleMat_ = IdentityMat4;
} 

void Node2DComponent::tryCalcTranslateMat() {
    if (position_.IsChanged()) {
        translateMat_ = CreateTranslate(Vec3(position.x, position.y, 0));
        position_.ClearChangeState();
    }
}

void Node2DComponent::tryCalcScaleMat() {
    if (scale_.IsChanged()) {
        scaleMat_ = CreateScale(Vec3(scale.x, scale.y, 1));
        scale_.ClearChangeState();
    }
}

void Node2DComponent::tryCalcRotateMat() {
    if (rotation_.IsChanged()) {
        rotationMat_ = CreateRotationZ(rotation);
        rotation_.ClearChangeState();
    }
}

bool Node2DComponent::TryUpdateLocalTransform() {
    if (position_.IsChanged() || rotation_.IsChanged() || scale_.IsChanged()) {
        tryCalcRotateMat();
        tryCalcScaleMat();
        tryCalcTranslateMat();
        localTransform_ = translateMat_ * rotationMat_ * scaleMat_;
        return true;
    }
    return false;
}

}