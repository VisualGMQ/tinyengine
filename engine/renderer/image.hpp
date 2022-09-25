#pragma once

#include "engine/renderer/renderer.hpp"

namespace engine {

class DLLEXPORT Image final {
public:
    Image(Texture* texture, const Rect& rect);
    Image(Texture* texture);
    Image& SetColor(const Color& color) { color_ = color; return *this; }
    const Color& GetColor() const { return color_; }

    Image& SetSize(const Size& size) { size_ = size; return *this; }
    const Size& GetSize() const { return size_; }
    Image& SetPosition(const Vec2&);
    const Vec2& GetPosition() const { return position_; }
    Image& SetRotation(float);
    float GetRotation() const { return rotation_; }
    Image& SetScale(const Vec2&);
    const Vec2& GetScale() const { return scale_; }
    Image& SetAnchor(const Vec2&);
    const Vec2& GetAnchor() const { return anchor_; }
    const Mat4& GetTransform() const { return transform_; }

    void Draw(const Mat4& = IdentityMat4);

private:
    Texture* texture_;
    Color color_;

    enum Dirt {
        None = 0,
        Rotation = 0x01,
        Translate = 0x02,
        Scale = 0x04,
        Anchor = 0x10,
    };
    unsigned int dirt_;

    Mat4 transform_;
    Mat4 rotationMat_;
    Mat4 translateMat_;
    Mat4 scaleMat_;
    Mat4 anchorMat_;

    Rect srcrect_;
    Vec2 position_;
    float rotation_ = 0;
    Vec2 size_;
    Vec2 scale_;
    Vec2 anchor_;

    Image();
    void tryCalcAnchorMat();
    void tryCalcTranslateMat();
    void tryCalcScaleMat();
    void tryCalcRotateMat();
    void tryCalcTransformMat();
};

}
