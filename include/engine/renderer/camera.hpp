#pragma once

#include "engine/core/vmath.hpp"

namespace engine {

class DLLEXPORT Camera {
public:
    virtual ~Camera() = default;

    virtual const Mat4& Project() = 0;
    virtual const Mat4& View() = 0;
};

class DLLEXPORT OrthoCamera: public Camera {
public:
    OrthoCamera(float w, float h, float near);
    const Mat4& Project() override;
    const Mat4& View() override;
    void MoveTo(const Vec3& pos);
    void Move(const Vec3& offset);
    Vec3 Position() const { return position_; }

private:
    bool isDirt_;
    Vec3 position_;
    Mat4 project_;
    Mat4 transform_;
    void tryCalcViewMat();
};

class DLLEXPORT PerspCamera: public Camera {
public:
    PerspCamera(float fov, float aspect, float znear, float zfar);
    const Mat4& Project() override;
    const Mat4& View() override;

    Vec3 Position() const { return position_; }

    void MoveFront(float offset);
    void MoveRight(float offset);
    void MoveUp(float offset);

    void Move(const Vec3& offset);
    void MoveTo(const Vec3& pos);
    void RotateTo(float x, float y);
    void Lookat(const Vec3& position);

private:
    Vec3 front_;
    Vec3 right_;
    Vec3 up_;
    Vec3 position_;
    Vec2 rotation_;
    bool isDirt_;
    Mat4 project_;
    Mat4 transform_;
    void tryCalcViewMat();
};

}
