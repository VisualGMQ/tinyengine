#include "engine/renderer/camera.hpp"

namespace engine {

EmptyCamera::EmptyCamera(): project_(CreateIdentityMat<4>()), transform_(CreateIdentityMat<4>()) {}
const Mat4& EmptyCamera::GetProject() const {
    return project_;
}

const Mat4& EmptyCamera::GetView() const {
    return transform_;
}

OrthoCamera::OrthoCamera(float w, float h, float near) {
    project_ = CreateOrtho(w, h, near);
    transform_ = CreateIdentityMat<4>();
}

const Mat4& OrthoCamera::GetProject() const {
    return project_;
}

const Mat4& OrthoCamera::GetView() const {
    return transform_;
}


PerspCamera::PerspCamera(float fov, float aspect, float znear, float zfar) {
    project_ = CreatePersp(fov, aspect, znear, zfar);
    transform_ = CreateIdentityMat<4>();
}

const Mat4& PerspCamera::GetProject() const {
    return project_;
}

const Mat4& PerspCamera::GetView() const {
    return transform_;
}

}
