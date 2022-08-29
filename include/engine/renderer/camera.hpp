#pragma once

#include "engine/core/vmath.hpp"

namespace engine {

class Camera {
public:
    virtual ~Camera() = default;

    virtual const Mat4& GetProject() = 0;
    virtual const Mat4& GetView() = 0;
};

class OrthoCamera: public Camera {
public:
    OrthoCamera(float w, float h, float near);
    const Mat4& GetProject() override;
    const Mat4& GetView() override;
    void MoveTo(const Vec3& pos);
    void Move(const Vec3& offset);
    const Vec3& Position() { return position_; }

private:
    bool isDirt_;
    Vec3 position_;
    Mat4 project_;
    Mat4 transform_;
    void tryCalcViewMat();
};

class PerspCamera: public Camera {
public:
    PerspCamera(float fov, float aspect, float znear, float zfar);
    const Mat4& GetProject() override;
    const Mat4& GetView() override;

private:
    bool isDirt_;
    Mat4 project_;
    Mat4 transform_;
    void tryCalcViewMat();
};

}
