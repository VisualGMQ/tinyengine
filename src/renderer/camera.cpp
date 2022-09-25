#include "engine/renderer/camera.hpp"

namespace engine {

OrthoCamera::OrthoCamera(float w, float h, float near, float far)
    : isDirt_(true), position_(0, 0, 0),
      project_(CreateOrtho(w, h, near, far)),
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

const Mat4& OrthoCamera::Project() {
    return project_;
}

const Mat4& OrthoCamera::View() {
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
    : fov_(fov), aspect_(aspect), znear_(znear), zfar_(zfar),
      needRecalcProject_(true),
      isDirt_(true), transform_(CreateIdentityMat<4>()),
      front_(0, 0, 1) {
}

void PerspCamera::SetFov(float fov) {
    if (fov_ != fov) {
        fov_ = fov;
        needRecalcProject_ = true;
    }
}

void PerspCamera::SetAspect(float aspect) {
    if (aspect != aspect_) {
        aspect_ = aspect;
        needRecalcProject_ = true;
    }
}

void PerspCamera::SetNear(float znear) {
    if (znear != znear_) {
        znear_ = znear;
        needRecalcProject_ = true;
    }
}

void PerspCamera::SetFar(float zfar) {
    if (zfar != zfar_) {
        zfar_ = zfar;
        needRecalcProject_ = true;
    }
}

const Mat4& PerspCamera::Project() {
    if (needRecalcProject_) {
        needRecalcProject_ = false;
        project_ = CreatePersp(fov_, aspect_, znear_, zfar_);
    }
    return project_;
}

const Mat4& PerspCamera::View() {
    tryCalcViewMat();
    return transform_;
}

void PerspCamera::tryCalcViewMat() {
    if (isDirt_) {
        isDirt_ = false;
        if (std::abs(Length2(front_) - 1) >= std::numeric_limits<float>::epsilon()) {
            front_ = Normalize(front_);
        }
        right_ = Normalize(Cross(Vec3(0, 1, 0), front_));
        up_ = Normalize(Cross(front_, right_));
        transform_ = CreateLookAt(right_, up_, front_, position_);
    }
}

void PerspCamera::Lookat(const Vec3& position) {
    isDirt_ = false;
    front_ = Normalize(position_ - position);
    right_ = Normalize(Cross(Vec3(0, 1, 0), front_));
    up_ = Normalize(Cross(front_, right_));
    transform_ = CreateLookAt(right_, up_, front_, position_);
}

void PerspCamera::MoveFront(float offset) {
    position_ -= offset * front_;
    isDirt_ = true;
}

void PerspCamera::MoveRight(float offset) {
    position_ += offset * right_;
    isDirt_ = true;
}

void PerspCamera::MoveUp(float offset) {
    position_.y += offset ;
    isDirt_ = true;
}

void PerspCamera::Move(const Vec3& offset) {
    position_ += offset;
    isDirt_ = true;
}

void PerspCamera::MoveTo(const Vec3& pos) {
    position_ = pos;
    isDirt_ = true;
}

void PerspCamera::RotateTo(float x, float y) {
    front_ = RotateWithQuat(Vec3(0, 0, 1), x, Vec3(1, 0, 0));
    front_ = RotateWithQuat(front_,  y, Vec3(0, 1, 0));
    isDirt_ = true;
}

}
