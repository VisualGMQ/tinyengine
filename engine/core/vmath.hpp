#pragma once

#include "engine/core/log.hpp"
#include "engine/core/dllexport.hpp"

#include <algorithm>
#include <iostream>
#include <cmath>

namespace engine {

template <typename T, unsigned int W, unsigned int H>
class DLLEXPORT Mat final {
public:
    Mat() {
        memset(data_, 0, sizeof(T) * W * H);
    }

    Mat(const std::initializer_list<T>& list) {
        if (list.size() != W * H) {
            Loge("list.size != W * H");
        } else {
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    Get(j, i) = *(list.begin() + i * W + j);
                }
            }
        }
    }

    Mat& operator=(const Mat& o) {
        memcpy(data_, o.data_, sizeof(T) * W * H);
        return *this;
    }

    T& operator()(unsigned int x, unsigned int y) {
        return Get(x, y);
    }

    const T& operator()(unsigned int x, unsigned int y) const {
        return Get(x, y);
    }

    T& Get(unsigned int x, unsigned int y) {
        return data_[y + x * H];
    }

    const T& Get(unsigned int x, unsigned int y) const {
        return data_[y + x * H];
    }

    unsigned int Height() const { return H; }
    unsigned int Width() const { return W; }

    template <typename U>
    Mat& operator+=(const Mat<U, W, H>& o) {
        for (int i = 0; i < W * H; i++) {
            data_[i] += o.data_[i];
        }
        return *this;
    }

    template <typename U>
    Mat& operator-=(const Mat<U, W, H>& o) {
        for (int i = 0; i < W * H; i++) {
            data_[i] -= o.data_[i];
        }
        return *this;
    }

    template <typename U>
    Mat& operator*=(const U& value) {
        for (int i = 0; i < W * H; i++) {
            data_[i] *= value;
        }
        return *this;
    }

    template <typename U>
    Mat& operator/=(const U& value) {
        for (int i = 0; i < W * H; i++) {
            data_[i] /= value;
        }
        return *this;
    }

    T* Data() { return data_; }
    const T* Data() const { return data_; }

private:
    T data_[W * H];
};


template <typename T, typename U, unsigned int W, unsigned int H>
DLLEXPORT inline bool operator==(const Mat<T, W, H>& m, const Mat<U, W, H>& o) {
    for (int i = 0; i < W * H; i++) {
        if (m.Data()[i] != o.Data()[i])
            return false;
    }
    return true;
}

template <typename T, typename U, unsigned int W, unsigned int H>
DLLEXPORT inline bool operator!=(const Mat<T, W, H>& m, const Mat<U, W, H>& o) {
    return !(m == o);
}

template <typename T, typename U, unsigned int W, unsigned int H>
DLLEXPORT inline auto operator+(const Mat<T, W, H>& m, const Mat<U, W, H>& o) {
    Mat<std::common_type_t<U, T>, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.Data()[i] = m.Data()[i] + o.Data()[i];
    }
    return result;
}

template <typename T, typename U, unsigned int W, unsigned int H>
DLLEXPORT inline auto operator-(const Mat<T, W, H>& m, const Mat<U, W, H>& o) {
    Mat<std::common_type_t<U, T>, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.Data()[i] = m.Data()[i] - o.Data()[i];
    }
    return result;
}

template <typename T, unsigned int W, unsigned int H>
DLLEXPORT inline auto operator*(const Mat<T, W, H>& m, float value) {
    Mat<T, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.Data()[i] = m.Data()[i] * value;
    }
    return result;
}

template <typename T, unsigned int W, unsigned int H>
DLLEXPORT inline auto operator*(float value, const Mat<T, W, H>& m2) {
    return m2 * value;
}

template <typename T, typename U, unsigned int W, unsigned int H>
DLLEXPORT inline auto operator/(const Mat<T, W, H>& m, const U& value) {
    Mat<std::common_type_t<U, T>, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.Data()[i] = m.Data()[i] / value;
    }
    return result;
}

template <typename T, typename U, unsigned int W, unsigned int H, unsigned int UW>
DLLEXPORT inline auto operator*(const Mat<T, W, H>& m, const Mat<U, UW, W>& o) {
    Mat<std::common_type_t<U, T>, H, UW> result;
    for (int i = 0; i < H; i++) {
        for (int j = 0 ; j < UW; j++) {
            result(j, i) = 0;
            for (int k = 0; k < W; k++) {
                result(j, i) += m.Get(k, i) * o.Get(j, k);
            }
        }
    }
    return result;
}

template <typename T, typename U, unsigned int W, unsigned int H>
DLLEXPORT inline auto MulEach(const Mat<T, W, H>& m1, const Mat<U, W, H>& m2) {
    Mat<std::common_type_t<T, U>, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.Data()[i] = m1.Data()[i] * m2.Data()[i];
    }
    return result;
}

template <typename T, unsigned int W, unsigned int H>
DLLEXPORT inline auto operator-(const Mat<T, W, H>& m) {
    return m * -1;
}

template <typename T, unsigned int W, unsigned int H>
DLLEXPORT inline std::ostream& operator<<(std::ostream& o, const Mat<T, W, H>& m) {
    o << "[" << std::endl;
    for (int i = 0 ; i < H; i++) {
        for (int j = 0 ; j < W; j++) {
            o << m(j, i) << ", ";
        }
        o << std::endl;
    }
    o << "]";
    return o;
}

template <unsigned int Len>
DLLEXPORT inline Mat<float, Len, Len> CreateZeroMat() {
    return Mat<float, Len, Len>();
}

template <unsigned int Len>
DLLEXPORT inline Mat<float, Len, Len> CreateIdentityMat() {
    auto mat = Mat<float, Len, Len>();
    for (int i = 0; i < Len; i++) {
        mat(i, i) = 1;
    }
    return mat;
}

template <unsigned int Len>
DLLEXPORT inline Mat<float, Len, Len> CreateOnesMat() {
    auto mat = Mat<float, Len, Len>();
    for (int i = 0; i < Len * Len; i++) {
        mat(i % Len, i / Len) = 1;
    }
    return mat;
}

template <typename T>
class DLLEXPORT Mat<T, 1, 3> final {
public:
    Mat() {
        memset(data_, 0, sizeof(T) * 3);
    }

    Mat(T x, T y, T z) {
        Set(x, y, z);
    }

    void Set(T x, T y, T z){
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }

    Mat& operator=(const Mat& o) {
        memcpy(data_, o.data_, sizeof(T) * 3);
        return *this;
    }

    T& operator()(unsigned int x, unsigned int y) {
        return Get(x, y);
    }

    const T& operator()(unsigned int x, unsigned int y) const {
        return Get(x, y);
    }

    T& Get(unsigned int x, unsigned int y) {
        return data_[y + x * 3];
    }

    const T& Get(unsigned int x, unsigned int y) const {
        return data_[y + x * 3];
    }

    T* Data() { return data_; }
    const T* Data() const { return data_; }

    unsigned int Height() const { return 3; }
    unsigned int Width() const { return 1; }

    template <typename U>
    Mat& operator+=(const Mat<U, 1, 3>& o) {
        for (int i = 0; i < 3; i++) {
            data_[i] += o.data_[i];
        }
        return *this;
    }

    template <typename U>
    Mat& operator-=(const Mat<U, 1, 3>& o) {
        for (int i = 0; i < 3; i++) {
            data_[i] -= o.data_[i];
        }
        return *this;
    }

    template <typename U>
    Mat& operator*=(const U& value) {
        for (int i = 0; i < 3; i++) {
            data_[i] *= value;
        }
        return *this;
    }

    template <typename U>
    Mat& operator/=(const U& value) {
        for (int i = 0; i < 3; i++) {
            data_[i] /= value;
        }
        return *this;
    }

    union {
        T data_[3];
        struct { T x, y, z; };
    };
};

using Mat2 = Mat<float, 2, 2>;
using Mat3 = Mat<float, 3, 3>;
using Mat4 = Mat<float, 4, 4>;
using Vec3 = Mat<float, 1, 3>;


template <typename T>
class DLLEXPORT Mat<T, 1, 2> final {
public:
    Mat() {
        memset(data_, 0, sizeof(T) * 2);
    }

    Mat(T x, T y) {
        Set(x, y);
    }

    void Set(T x, T y){
        data_[0] = x;
        data_[1] = y;
    }

    Mat& operator=(const Mat& o) {
        memcpy(data_, o.data_, sizeof(T) * 2);
        return *this;
    }

    T& operator()(unsigned int x, unsigned int y) {
        return Get(x, y);
    }

    const T& operator()(unsigned int x, unsigned int y) const {
        return Get(x, y);
    }

    T& Get(unsigned int x, unsigned int y) {
        return data_[y + x * 2];
    }

    const T& Get(unsigned int x, unsigned int y) const {
        return data_[y + x * 2];
    }

    T* Data() { return data_; }
    const T* Data() const { return data_; }

    unsigned int Height() const { return 2; }
    unsigned int Width() const { return 1; }

    template <typename U>
    Mat& operator+=(const Mat<U, 1, 2>& o) {
        for (int i = 0; i < 2; i++) {
            data_[i] += o.data_[i];
        }
        return *this;
    }

    template <typename U>
    Mat& operator-=(const Mat<U, 1, 2>& o) {
        for (int i = 0; i < 2; i++) {
            data_[i] -= o.data_[i];
        }
        return *this;
    }

    template <typename U>
    Mat& operator*=(const U& value) {
        for (int i = 0; i < 2; i++) {
            data_[i] *= value;
        }
        return *this;
    }

    template <typename U>
    Mat& operator/=(const U& value) {
        for (int i = 0; i < 2; i++) {
            data_[i] /= value;
        }
        return *this;
    }

    union {
        T data_[2];
        struct { T x, y; };
        struct { T w, h; };
    };
};

using Vec2 = Mat<float, 1, 2>;
using Size = Mat<float, 1, 2>;


template <typename T>
class DLLEXPORT Mat<T, 1, 4> final {
public:
    Mat() {
        memset(data_, 0, sizeof(T) * 4);
    }

    Mat(T x, T y, T z, T w = 1) {
        Set(x, y, z, w);
    }

    void Set(T x, T y, T z, T w = 1) {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
        data_[3] = w;
    }

    Mat& operator=(const Mat& o) {
        memcpy(data_, o.data_, sizeof(T) * 4);
        return *this;
    }

    T& operator()(unsigned int x, unsigned int y) {
        return Get(x, y);
    }

    const T& operator()(unsigned int x, unsigned int y) const {
        return Get(x, y);
    }

    T& Get(unsigned int x, unsigned int y) {
        return data_[y + x * 4];
    }

    const T& Get(unsigned int x, unsigned int y) const {
        return data_[y + x * 4];
    }

    T* Data() { return data_; }
    const T* Data() const { return data_; }

    unsigned int Height() const { return 4; }
    unsigned int Width() const { return 1; }

    template <typename U>
    Mat& operator+=(const Mat<U, 1, 4>& o) {
        for (int i = 0; i < 4; i++) {
            data_[i] += o.data_[i];
        }
        return *this;
    }

    template <typename U>
    Mat& operator-=(const Mat<U, 1, 4>& o) {
        for (int i = 0; i < 4; i++) {
            data_[i] -= o.data_[i];
        }
        return *this;
    }

    template <typename U>
    Mat& operator*=(const U& value) {
        for (int i = 0; i < 4; i++) {
            data_[i] *= value;
        }
        return *this;
    }

    template <typename U>
    Mat& operator/=(const U& value) {
        for (int i = 0; i < 4; i++) {
            data_[i] /= value;
        }
        return *this;
    }

    union {
        T data_[4];
        struct { T x, y, z, w; };
        struct { T r, g, b, a; };
    };
};

using Vec4 = Mat<float, 1, 4>;
using Color = Mat<float, 1, 4>;

template <typename T, unsigned int N>
using Vec = Mat<T, 1, N>;

template <typename T, unsigned int N>
DLLEXPORT inline T Dot(const Vec<T, N>& v1, const Vec<T, N>& v2) {
    T result = T{};
    for (int i = 0; i < N; i++) {
        result += v1(0, i) * v2(0, i);
    }
    return result;
}

DLLEXPORT inline float Cross(const Vec2& v1, const Vec2& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

DLLEXPORT inline Vec3 Cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}

template <typename T, unsigned int N>
DLLEXPORT inline T Length2(const Vec<T, N>& v) {
    T sum = 0;
    for (int i = 0; i < N; i++) {
        sum += v(0, i) * v(0, i);
    }
    return sum;
}

template <typename T, unsigned int N>
DLLEXPORT inline T Length(const Vec<T, N>& v) {
    return std::sqrt(Length2(v));
}

template <typename T, unsigned int N>
DLLEXPORT inline auto Normalize(const Vec<T, N>& v) {
    return v / Length(v);
}

template <typename T, unsigned int W, unsigned int H>
DLLEXPORT inline auto Transpose(const Mat<T, W, H>& m) {
    Mat<T, H, W> result;
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            result(j, i) = m(i, j);
        }
    }
    return result;
}

DLLEXPORT inline Mat4 CreateOrtho(float w, float h, float depth) {
    return Mat4({
        2 / w,     0,         0, -1,
            0,-2 / h,         0,  1,
            0,     0, 2 / depth,  0,
            0,     0,         0,  1,
        });
}

DLLEXPORT inline Mat4 CreatePersp(float fov, float aspect, float near, float far) {
    float half_fov = std::tan(0.5 * fov);
    return Mat4({
            1 / (aspect * half_fov), 0,                             0,  0,
            0,            1 / half_fov,                             0,  0,
            0,                       0,   (near + far) / (near - far), 2 * near * far / (near - far),
            0,                       0,  -1,  0,
        });
}

struct DLLEXPORT Rect {
    Vec2 position;
    Vec2 size;

    Rect() = default;
    Rect(float x, float y, float w, float h): position(x, y), size(w, h) {}
    Rect(const Vec2& pos, const Vec2& size) : position(pos), size(size) {}
};

DLLEXPORT inline std::ostream& operator<<(std::ostream& o, const Rect& rect) {
    o << "Rect(" << rect.position << ", " << rect.size << ")";
    return o;
}

constexpr float PI = 3.14159265358;

DLLEXPORT inline float Radians(float degrees) {
    return degrees * PI / 180.0;
}

DLLEXPORT inline float Degrees(float radians) {
    return radians * 180.0 / PI;
}

DLLEXPORT inline Vec3 Radians(const Vec3& v) {
    return Vec3(Radians(v.x), Radians(v.y), Radians(v.z));
}

DLLEXPORT inline Vec3 Degrees(const Vec3& v) {
    return Vec3(Degrees(v.x), Degrees(v.y), Degrees(v.z));
}

template <typename T>
class DLLEXPORT Quaternion final {
public:
    Quaternion();
    Quaternion(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {}
    Quaternion(const Vec<T, 3>& v, T s): v(v), s(s) {}

    template <typename U>
    Quaternion& operator+=(const Quaternion<U>& q) {
        *this = q + *this;
        return *this;
    }

    template <typename U>
    Quaternion& operator-=(const Quaternion<U>& q) {
        *this = q - *this;
        return *this;
    }

    template <typename U>
    Quaternion& operator/=(const U& value) {
        *this = *this / value;
        return *this;
    }

    template <typename U>
    Quaternion& operator*=(const U& value) {
        *this = *this * value;
        return *this;
    }

    template <typename U>
    Quaternion& operator*=(const Quaternion<U>& q) {
        *this = *this * q;
        return *this;
    }

    union {
        struct { Vec<T, 3> v; T s; };
        struct { T x, y, z, w; };
    };
};

// Hamilton Product
template <typename T, typename U>
DLLEXPORT inline auto operator*(const Quaternion<T>& q1, const Quaternion<U>& q2) {
    return Quaternion<std::common_type_t<T, U>>(q1.v * q2.s + q1.s * q2.v + Cross(q1.v, q2.v), q1.s * q2.s - Dot(q1.v, q2.v));
}

template <typename T, typename U>
DLLEXPORT inline auto operator*(const U& value, const Quaternion<U>& q2) {
    return Quaternion<std::common_type_t<T, U>>(q2.v * value, q2.s * value);
}

template <typename T, typename U>
DLLEXPORT inline auto operator*(const Quaternion<U>& q2, const U& value) {
    return value * q2;
}

template <typename T, typename U>
DLLEXPORT inline auto operator/(const Quaternion<U>& q2, const U& value) {
    return Quaternion<std::common_type_t<T, U>>(q2.v / value, q2.s / value);
}

template <typename T, typename U>
DLLEXPORT inline auto Dot(const Quaternion<T>& q1, const Quaternion<T>& q2) {
    return Dot(q1.v, q2.v) + q1.s * q2.s;
}

template <typename T, typename U>
DLLEXPORT inline auto operator+(const Quaternion<T>& q1, const Quaternion<U>& q2) {
    return Quaternion<std::common_type_t<T, U>>(q1.v + q2.v, q1.s + q2.s);
}

template <typename T, typename U>
DLLEXPORT inline auto operator-(const Quaternion<T>& q1, const Quaternion<U>& q2) {
    return Quaternion<std::common_type_t<T, U>>(q1.v - q2.v, q1.s - q2.s);
}

template <typename T>
DLLEXPORT inline auto Length2(const Quaternion<T>& q) {
    return Length2(q.v) + q.s * q.s;
}

template <typename T>
DLLEXPORT inline auto Length(const Quaternion<T>& q) {
    return std::sqrt(Length2(q));
}

template <typename T>
DLLEXPORT inline auto Conjugate(const Quaternion<T>& q) {
    return Quaternion<T>(-q.v, q.s);
}

template <typename T>
DLLEXPORT inline auto Inverse(const Quaternion<T>& q) {
    return Conjugate(q) / Dot(q, q);
}

template <typename T>
DLLEXPORT inline auto Normalize(const Quaternion<T>& q) {
    return q / Length(q);
}

DLLEXPORT inline Mat4 CreateTranslate(const Vec3& translate) {
    return Mat4{
        1, 0, 0, translate.x,
        0, 1, 0, translate.y,
        0, 0, 1, translate.z,
        0, 0, 0,           1,
    };
}

DLLEXPORT inline Mat4 CreateScale(const Vec3& scale) {
    return Mat4{
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1,
    };
}

DLLEXPORT inline Mat4 CreateAxisRotationWithQuat(const Vec3& axis, float rotation) {
    float half_angle = rotation * 0.5;
    float sin = std::sin(half_angle);
    float cos = std::cos(half_angle);
    float x = axis.x * sin;
    float y = axis.y * sin;
    float z = axis.z * sin;
    float w = cos;
    return Mat4{
        1 - 2 * y * y - 2 * z * z, 2 * x * y + 2 * z * w, 2 * x * y - 2 * y * w, 0,
        2 * x * y - 2 * z * w, 1 - 2 * x * x - 2 * z * z, 2 * y * z + 2 * x * w, 0,
        2 * x * z + 2 * y * w, 2 * y * z - 2 * x * w, 1 - 2 * x * x - 2 * y * y, 0,
        0, 0, 0, 1,
    };
}

DLLEXPORT inline Mat4 CreateAxisRotationWithEular(const Vec3& axis, float rotation) {
    float c = std::cos(rotation),
          s = std::sin(rotation),
          d = 1 - c; 
    const float& x = axis.x;
    const float& y = axis.y;
    const float& z = axis.z;
    return Mat4{
        c + d * x * x, d * x * y - s * z, d * x * z + s * y, 0,
        d * x * y + s * z, c + d * y * y, d * y * z - s * x, 0,
        d * x * z - s * y, d * y * z + s * x, c + d * z * z, 0,
        0, 0, 0, 1,
    };
}

DLLEXPORT inline Vec3 Translate(const Vec3& v, const Vec3& pos) {
    return v + pos;
}

DLLEXPORT inline Vec3 Scale(const Vec3& v, const Vec3& scale) {
    return MulEach(v, scale);
}

DLLEXPORT inline Vec3 RotateWithQuat(const Vec3& v, float angle, const Vec3& axis) {
    float half_angle = angle * 0.5;
    float half_sin = std::sin(half_angle);
    Quaternion<float> q(axis.x * half_sin, axis.y * half_sin, axis.z * half_sin,
                        std::cos(half_angle));
    Quaternion<float> m(v.x, v.y, v.z, 1);
    return v + Cross(2 * q.v, Cross(q.v, v) + q.s * v);
}

DLLEXPORT inline Mat4 CreateRotationX(float angle) {
    float cx = std::cos(angle),
          sx = std::sin(angle);
    return Mat4{
        1, 0, 0, 0,
        0, cx, -sx, 0,
        0, sx, cx, 0,
        0, 0, 0, 1,
    };
}

DLLEXPORT inline Mat4 CreateRotationY(float angle) {
    float cy = std::cos(angle),
          sy = std::sin(angle);
    return Mat4{
        cy, 0, sy, 0,
        0, 1, 0, 0,
        -sy, 0, cy, 0,
        0, 0, 0, 1,
    };
}

DLLEXPORT inline Mat4 CreateRotationZ(float angle) {
    float cz = std::cos(angle),
          sz = std::sin(angle);
    return Mat4 {
        cz, -sz, 0, 0,
        sz, cz, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 1,
    };
}

DLLEXPORT inline Mat4 CreateSRT(const Vec3& pos, const Vec3& rotation, const Vec3& scale) {
    return
        Mat4{
            1, 0, 0, pos.x,
            0, 1, 0, pos.y,
            0, 0, 1, pos.z,
            0, 0, 0, 1,
        } *
        CreateRotationX(rotation.x) * CreateRotationY(rotation.y) * CreateRotationZ(rotation.z) *
        Mat4{
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, 0, 0, 1,
        };
}

DLLEXPORT inline Mat4 CreateLookAt(const Vec3& right, const Vec3& up, const Vec3& front, const Vec3& position) {
    return Mat4{
        right.x, right.y, right.z, -(position.x * right.x + position.y * right.y + position.z * right.z),
           up.x,    up.y,    up.z, -(position.x * up.x + position.y * up.y +  position.z * up.z),
        front.x, front.y, front.z, -(position.x * front.x + position.y * front.y + position.z * front.z),
        0, 0, 0, 1,
    };
}

template <typename T>
DLLEXPORT inline T Clamp(const T& value, const T& low, const T& high) {
    return value > high ? high : (value < low ? low : value);
}

DLLEXPORT inline bool IsPointInRect(const Vec2& p, const Rect& r) {
    return p.x >= r.position.x && p.x <= r.position.x + r.size.w &&
           p.y >= r.position.y && p.y <= r.position.y + r.size.h;
}

DLLEXPORT extern const Mat4 IdentityMat4;

}
