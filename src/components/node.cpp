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

    position = Vec2(0, 0);
    scale = Vec2(1, 1);
    rotation = 0;

    zIndex = 0;

    localTransform_ = IdentityMat4;
    globalTransform_ = IdentityMat4;
    rotationMat_ = IdentityMat4;
    translateMat_ = IdentityMat4;
    scaleMat_ = IdentityMat4;
} 

void Node2DComponent::DetectDirt() {
    if (oldPosition_ != position) {
        dirt_ |= Dirt::Translate;
        oldPosition_ = position;
    }
    if (oldRotation_ != rotation) {
        dirt_ |= Dirt::Rotate;
        oldRotation_ = rotation;
    }
    if (oldScale_ != scale) {
        dirt_ |= Dirt::Scale;
        oldScale_ = scale;
    }
}

void Node2DComponent::tryCalcTranslateMat() {
    if (dirt_ & Dirt::Translate) {
        translateMat_ = CreateTranslate(Vec3(position.x, position.y, 0));
        dirt_ &= ~Dirt::Translate;
    }
}

void Node2DComponent::tryCalcScaleMat() {
    if (dirt_ & Dirt::Scale) {
        scaleMat_ = CreateScale(Vec3(scale.x, scale.y, 1));
        dirt_ &= ~Dirt::Scale;
    }
}

void Node2DComponent::tryCalcRotateMat() {
    if (dirt_ & Dirt::Rotate) {
        rotationMat_ = CreateRotationZ(rotation);
        dirt_ &= ~Dirt::Rotate;
    }
}

bool Node2DComponent::TryUpdateLocalTransform() {
    if (dirt_ != Dirt::None) {
        tryCalcRotateMat();
        tryCalcScaleMat();
        tryCalcTranslateMat();
        localTransform_ = translateMat_ * rotationMat_ * scaleMat_;
        return true;
    }
    return false;
}

}