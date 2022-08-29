#include "engine/renderer/camera.hpp"

namespace engine {

OrthoCamera::OrthoCamera(float w, float h, float near)
    : isDirt_(true), position_(0, 0, 0),
      project_(CreateOrtho(w, h, near)),
      transform_(CreateIdentityMat<4>()) {
}

void OrthoCamera::MoveTo(const Vec3& pos) {
    position_ = pos;
    isDirt_ = true;
}

void OrthoCamera::Move(const Vec3& offset) {
    position_ += offset;
    isDirt_ = true;
}

const Mat4& OrthoCamera::GetProject() {
    return project_;
}

const Mat4& OrthoCamera::GetView() {
    tryCalcViewMat();
    return transform_;
}

void OrthoCamera::tryCalcViewMat() {
    if (isDirt_) {
        transform_(3, 0) = -position_.x;
        transform_(3, 1) = -position_.y;
        transform_(3, 2) = -position_.z;
        isDirt_ = false;
    }
}


PerspCamera::PerspCamera(float fov, float aspect, float znear, float zfar)
    : isDirt_(true), project_(CreatePersp(fov, aspect, znear, zfar)), transform_(CreateIdentityMat<4>()) {
}

const Mat4& PerspCamera::GetProject() {
    return project_;
}

const Mat4& PerspCamera::GetView() {
    tryCalcViewMat();
    return transform_;
}

void PerspCamera::tryCalcViewMat() {
    if (isDirt_) {
        // TODO not finish
        isDirt_ = false;
    }
}

}
