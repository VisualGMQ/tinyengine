#include "engine/renderer/image.hpp"

namespace engine {

Image::Image() {
    texture_ = nullptr;
    transform_ = CreateIdentityMat<4>();
    rotationMat_ = CreateIdentityMat<4>();
    translateMat_ = CreateIdentityMat<4>();
    scaleMat_ = CreateIdentityMat<4>();
    anchorMat_ = CreateIdentityMat<4>();
    dirt_ = None;

    position_.Set(0, 0);
    size_.Set(0, 0);
    rotation_ = 0;
    anchor_.Set(0, 0);
    scale_.Set(1, 1);
    color_.Set(1, 1, 1);
}

Image::Image(Texture* texture, const Rect& rect): Image() {
    texture_ = texture;
    srcrect_ = rect;
    size_ = rect.size;
}

Image::Image(Texture* texture): Image() {
    texture_ = texture;
    srcrect_.position.Set(0, 0);
    srcrect_.size.Set(texture ? texture->Width() : 0,
                      texture ? texture->Height() : 0);
    size_ = srcrect_.size;
}

Image& Image::SetPosition(const Vec2& position) {
    position_ = position;
    dirt_ |= Dirt::Translate;
    return *this;
}

Image& Image::SetRotation(float rotation) {
    rotation_ = rotation;
    dirt_ |= Dirt::Rotation;
    return *this;
}

Image& Image::SetScale(const Vec2& scale) {
    scale_ = scale;
    dirt_ |= Dirt::Scale;
    return *this;
}

Image& Image::SetAnchor(const Vec2& anchor) {
    anchor_ = anchor;
    dirt_ |= Dirt::Anchor;
    return *this;
}

void Image::tryCalcTranslateMat() {
    if (dirt_ & Dirt::Translate) {
        translateMat_ = CreateTranslate(Vec3(position_.x, position_.y, 0));
        dirt_ &= ~Dirt::Translate;
    }
}

void Image::tryCalcAnchorMat() {
    if (dirt_ & Dirt::Anchor) {
        anchorMat_ = CreateTranslate(Vec3(-anchor_.x * size_.w, -anchor_.y * size_.h, 0));
        dirt_ &= ~Dirt::Anchor;
    }
}

void Image::tryCalcScaleMat() {
    if (dirt_ & Dirt::Scale) {
        scaleMat_ = CreateScale(Vec3(scale_.x, scale_.y, 1));
        dirt_ &= ~Dirt::Scale;
    }
}

void Image::tryCalcRotateMat() {
    if (dirt_ & Dirt::Rotation) {
        rotationMat_ = CreateRotationZ(rotation_);
        dirt_ &= ~Dirt::Rotation;
    }
}

void Image::tryCalcTransformMat() {
    if (dirt_ != Dirt::None) {
        tryCalcAnchorMat();
        tryCalcRotateMat();
        tryCalcScaleMat();
        tryCalcTranslateMat();
        transform_ = translateMat_ * rotationMat_ * scaleMat_ * anchorMat_;
    }
}

void Image::Draw(const Mat4& parentTransform) {
    if (!texture_) return;
    tryCalcTransformMat();
    Renderer::SetDrawColor(color_);
    Renderer::DrawTexture(*texture_, &srcrect_, size_, transform_ * parentTransform);
}

}
