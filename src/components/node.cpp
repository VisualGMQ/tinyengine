#include "engine/components/node.hpp"

namespace engine {

void Node2DComponent::Reset() {
    NodeComponent::Reset();

    dirt_ = None;
    position.Set(0, 0);
    scale.Set(1, 1);
    rotation = 0;

    transform_ = IdentityMat4;
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

bool Node2DComponent::TryUpdateTransform() {
    if (dirt_ != Dirt::None) {
        tryCalcRotateMat();
        tryCalcScaleMat();
        tryCalcTranslateMat();
        transform_ = translateMat_ * rotationMat_ * scaleMat_;
        return true;
    }
    return false;
}

}