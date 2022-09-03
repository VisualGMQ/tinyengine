#pragma once

#include "engine/renderer/renderer.hpp"

namespace engine {

class Image final {
public:
    Image(Texture* texture, const Rect& rect);
    Image(Texture* texture);
    void SetColor(const Color& color) { color_ = color; }
    const Color& GetColor() const { return color_; }

    void SetSize(const Size& size) { size_ = size; }
    const Size& GetSize() const { return size_; }
    void SetPosition(const Vec2&);
    const Vec2& GetPosition() const { return position_; }
    void SetRotation(float);
    float GetRotation() const { return rotation_; }
    void SetScale(const Vec2&);
    const Vec2& GetScale() const { return scale_; }
    void SetAnchor(const Vec2&);
    const Vec2& GetAnchor() const { return anchor_; }

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
    Mat4 anchorMat_;
    Mat4 scaleMat_;

    Rect srcrect_;
    Vec2 position_;
    Vec2 size_;
    Vec2 anchor_;
    Vec2 scale_;
    float rotation_ = 0;

    Image();
    void tryCalcTranslateMat();
    void tryCalcAnchorMat();
    void tryCalcScaleMat();
    void tryCalcRotateMat();
    void tryCalcTransformMat();
};

}
