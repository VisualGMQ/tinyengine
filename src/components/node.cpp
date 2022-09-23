#include "engine/components/node.hpp"

namespace engine {

void Node2DComponent::Reset() {
    NodeComponent::Reset();

    dirt_ = None;

    transform_ = IdentityMat4;
    rotationMat_ = IdentityMat4;
    translateMat_ = IdentityMat4;
    scaleMat_ = IdentityMat4;

    rotation_ = 0;
    scale_.Set(1, 1);
    position_.Set(0,0);
} 

void Node2DComponent::SetZIndex(float z) {
    zIndex_ = z;
}

Node2DComponent& Node2DComponent::SetPosition(const Vec2& position) {
    position_ = position;
    dirt_ |= Dirt::Translate;
    return *this;
}

Node2DComponent& Node2DComponent::SetRotation(float rotation) {
    rotation_ = rotation;
    dirt_ |= Dirt::Rotate;
    return *this;
}

Node2DComponent& Node2DComponent::SetScale(const Vec2& scale) {
    scale_ = scale;
    dirt_ |= Dirt::Scale;
    return *this;
}

void Node2DComponent::tryCalcTranslateMat() {
    if (dirt_ & Dirt::Translate) {
        translateMat_ = CreateTranslate(Vec3(position_.x, position_.y, 0));
        dirt_ &= ~Dirt::Translate;
    }
}

void Node2DComponent::tryCalcScaleMat() {
    if (dirt_ & Dirt::Scale) {
        scaleMat_ = CreateScale(Vec3(scale_.x, scale_.y, 1));
        dirt_ &= ~Dirt::Scale;
    }
}

void Node2DComponent::tryCalcRotateMat() {
    if (dirt_ & Dirt::Rotate) {
        rotationMat_ = CreateRotationZ(rotation_);
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