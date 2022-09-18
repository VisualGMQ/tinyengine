#include "engine/components/transform2d.hpp"

namespace engine {

void Transform2DComponent::Reset() {
    dirt_ = None;

    transform_ = IdentityMat4;
    rotationMat_ = IdentityMat4;
    translateMat_ = IdentityMat4;
    scaleMat_ = IdentityMat4;

    rotation_ = 0;
    scale_.Set(1, 1);
    position_.Set(0,0);
} 

Transform2DComponent& Transform2DComponent::SetPosition(const Vec2& position) {
    position_ = position;
    dirt_ |= Dirt::Translate;
    return *this;
}

Transform2DComponent& Transform2DComponent::SetRotation(float rotation) {
    rotation_ = rotation;
    dirt_ |= Dirt::Rotate;
    return *this;
}

Transform2DComponent& Transform2DComponent::SetScale(const Vec2& scale) {
    scale_ = scale;
    dirt_ |= Dirt::Scale;
    return *this;
}

void Transform2DComponent::tryCalcTranslateMat() {
    if (dirt_ & Dirt::Translate) {
        translateMat_ = CreateTranslate(Vec3(position_.x, position_.y, 0));
        dirt_ &= ~Dirt::Translate;
    }
}

void Transform2DComponent::tryCalcScaleMat() {
    if (dirt_ & Dirt::Scale) {
        scaleMat_ = CreateScale(Vec3(scale_.x, scale_.y, 1));
        dirt_ &= ~Dirt::Scale;
    }
}

void Transform2DComponent::tryCalcRotateMat() {
    if (dirt_ & Dirt::Rotate) {
        rotationMat_ = CreateRotationZ(rotation_);
        dirt_ &= ~Dirt::Rotate;
    }
}

bool Transform2DComponent::TryUpdateTransform() {
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