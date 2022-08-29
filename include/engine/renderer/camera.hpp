#pragma once

#include "engine/core/vmath.hpp"

namespace engine {

class Camera {
public:
    virtual ~Camera() = default;

    virtual const Mat4& GetProject() const = 0;
    virtual const Mat4& GetView() const = 0;
};

class OrthoCamera: public Camera {
public:
    OrthoCamera(float w, float h, float near);
    const Mat4& GetProject() const override;
    const Mat4& GetView() const override;

private:
    Mat4 project_;
    Mat4 transform_;
};

class PerspCamera: public Camera {
public:
    PerspCamera(float fov, float aspect, float znear, float zfar);
    const Mat4& GetProject() const override;
    const Mat4& GetView() const override;

private:
    Mat4 project_;
    Mat4 transform_;
};

}
