#pragma once

#include "engine/ecs/component.hpp"
#include "engine/core/vmath.hpp"

namespace engine {

class DLLEXPORT Transform2DComponent final: public Component {
public:
    Transform2DComponent(ComponentID id) : Component(id) { Reset(); }
    void Reset() override;

    Transform2DComponent& SetPosition(const Vec2&);
    const Vec2& GetPosition() const { return position_; }
    Transform2DComponent& SetRotation(float);
    float GetRotation() const { return rotation_; }
    Transform2DComponent& SetScale(const Vec2&);
    const Vec2& GetScale() const { return scale_; }

    bool TryUpdateTransform();
    const Mat4& GetTransform() const { return transform_; }

private:
    enum Dirt {
        None = 0,
        Translate = 0x01,
        Scale = 0x02,
        Rotate = 0x04,
    };
    uint32_t dirt_ = None;

    Mat4 transform_;
    Mat4 rotationMat_;
    Mat4 translateMat_;
    Mat4 scaleMat_;

    float rotation_;
    Vec2 scale_;
    Vec2 position_;

    void tryCalcScaleMat();
    void tryCalcTranslateMat();
    void tryCalcRotateMat();
};

}
