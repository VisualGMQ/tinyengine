#pragma once

#include "engine/core/log.hpp"
#include "engine/core/dllexport.hpp"

#include <algorithm>
#include <iostream>
#include <cmath>

namespace engine {

template <typename T, unsigned int W, unsigned int H>
class Mat final {
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
                    Get(j, i) = *(list.begin() + j * H + i);
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

    template <typename V, typename U, unsigned int OW, unsigned int OH>
    friend bool operator==(const Mat<V, OW, OH>& m, const Mat<U, OW, OH>& o);

    template <typename V, typename U, unsigned int OW, unsigned int OH>
    friend bool operator!=(const Mat<V, OW, OH>& m, const Mat<U, OW, OH>& o);

    template <typename V, typename U, unsigned int OW, unsigned int OH>
    friend bool operator+(const Mat<V, OW, OH>& m, const Mat<U, OW, OH>& o);

    template <typename V, typename U, unsigned int OW, unsigned int OH>
    friend bool operator-(const Mat<V, OW, OH>& m, const Mat<U, OW, OH>& o);

    template <typename V, typename U, unsigned int OW, unsigned int OH>
    friend bool operator*(const Mat<V, OW, OH>& m, const U& value);

    template <typename V, typename U, unsigned int OW, unsigned int OH>
    friend bool operator*(const U& value, const Mat<V, OW, OH>& m);

    template <typename V, typename U, unsigned int OW, unsigned int OH>
    friend bool operator/(const Mat<V, OW, OH>& m, const U& value);

private:
    T data_[W * H];
};


template <typename T, typename U, unsigned int W, unsigned int H>
bool operator==(const Mat<T, W, H>& m, const Mat<U, W, H>& o) {
    for (int i = 0; i < W * H; i++) {
        if (m.data_[i] != o.data_[i])
            return false;
    }
    return true;
}

template <typename T, typename U, unsigned int W, unsigned int H>
bool operator!=(const Mat<T, W, H>& m, const Mat<U, W, H>& o) {
    return !(m == o);
}

template <typename T, typename U, unsigned int W, unsigned int H>
auto operator+(const Mat<T, W, H>& m, const Mat<U, W, H>& o) {
    Mat<std::common_type_t<U, T>, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.data_[i] = m.data_[i] + o.data_[i];
    }
    return result;
}

template <typename T, typename U, unsigned int W, unsigned int H>
auto operator-(const Mat<T, W, H>& m, const Mat<U, W, H>& o) {
    Mat<std::common_type_t<U, T>, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.data_[i] = m.data_[i] - o.data_[i];
    }
    return result;
}

template <typename T, typename U, unsigned int W, unsigned int H>
auto operator*(const Mat<T, W, H>& m, const U& value) {
    Mat<std::common_type_t<U, T>, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.data_[i] = m.data_[i] * value;
    }
    return result;
}

template <typename T, typename U, unsigned int W, unsigned int H>
auto operator*(const U& value, const Mat<U, W, H>& m2) {
    return m2 * value;
}

template <typename T, typename U, unsigned int W, unsigned int H>
auto operator/(const Mat<T, W, H>& m, const U& value) {
    Mat<std::common_type_t<U, T>, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.data_[i] = m.data_[i] / value;
    }
    return result;
}


template <typename T, typename U, unsigned int W, unsigned int H, unsigned int UW>
auto operator*(const Mat<T, W, H>& m, const Mat<U, UW, W>& o) {
    Mat<std::common_type_t<U, T>, H, UW> result;
    for (int i = 0; i < H; i++) {
        for (int j = 0 ; j < UW; j++) {
            result(i, j) = 0;
            for (int k = 0; k < W; k++) {
                result(j, i) += m.Get(k, i) * o.Get(j, k);
            }
        }
    }
    return result;
}

template <typename T, unsigned int W, unsigned int H>
std::ostream& operator<<(std::ostream& o, const Mat<T, W, H>& m) {
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
Mat<float, Len, Len> CreateZeroMat() {
    return Mat<float, Len, Len>();
}

template <unsigned int Len>
Mat<float, Len, Len> CreateIdentityMat() {
    auto mat = Mat<float, Len, Len>();
    for (int i = 0; i < Len; i++) {
        mat(i, i) = 1;
    }
    return mat;
}

template <unsigned int Len>
Mat<float, Len, Len> CreateOnesMat() {
    auto mat = Mat<float, Len, Len>();
    for (int i = 0; i < Len * Len; i++) {
        mat(i % Len, i / Len) = 1;
    }
    return mat;
}

template <typename T>
class Mat<T, 1, 3> final {
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
class Mat<T, 1, 2> final {
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
class Mat<T, 1, 4> final {
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
T Dot(const Vec<T, N>& v1, const Vec<T, N>& v2) {
    T result = T{};
    for (int i = 0; i < N; i++) {
        result += v1(0, i) * v2(0, i);
    }
    return result;
}

inline float Cross(const Vec2& v1, const Vec2& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

inline Vec3 Cross(const Vec3& v1, const Vec3& v2) {
    return Vec3(v1.y * v2.z - v1.z * v2.y,
                v1.z * v2.x - v1.x * v2.z,
                v1.x * v2.y - v1.y * v2.x);
}

template <typename T, unsigned int N>
T Length2(const Vec<T, N>& v) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += v(0, i) * v(0, i);
    }
    return sum;
}

template <typename T, unsigned int N>
T Length(const Vec<T, N>& v) {
    return std::sqrt(Length2(v));
}

template <typename T, unsigned int N>
auto Normalize(const Vec<T, N>& v) {
    return v / Length(v);
}

template <typename T, unsigned int W, unsigned int H>
auto Transpose(const Mat<T, W, H>& m) {
    Mat<T, H, W> result;
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            result(j, i) = m(i, j);
        }
    }
    return result;
}

inline Mat4 CreateOrtho(float w, float h, float depth) {
    return Mat4({
        2 / w,     0,         0,  0,
            0,-2 / h,         0,  0,
            0,     0, 2 / depth,  0,
           -1,     1,         0,  1,
        });
}

inline Mat4 CreatePersp(float fov, float aspect, float near, float far) {
    float half_fov = tan(0.5 * fov);
    return Mat4({
            1 / (aspect * half_fov), 0,                           0,                             0,
            0,            1 / half_fov,                           0,                             0,
            0,                       0, (near + far) / (near - far), 2 * far * near / (near - far),
            0,                       0,                          -1,                             0,
        });
}

struct Rect {
    Vec2 position;
    Vec2 size;

    Rect() = default;
    Rect(float x, float y, float w, float h): position(x, y), size(w, h) {}
    Rect(const Vec2& pos, const Vec2& size) : position(pos), size(size) {}
};

constexpr float PI = 3.14159265358;

inline float Radians(float degrees) {
    return degrees * PI / 180.0;
}

inline float Degrees(float radians) {
    return radians * 180.0 / PI;
}

template <typename T>
class Quaternion final {
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
        struct { Vec<T, 4> v; T s; };
        struct { T x, y, z, w; };
    };
};

// Hamilton Product
template <typename T, typename U>
auto operator*(const Quaternion<T>& q1, const Quaternion<U>& q2) {
    return Quaternion<std::common_type_t<T, U>(q1.v * q2.s + q1.s * q2.v + Cross(q1.v, q2.v), q1.s * q2.s - Dot(q1.v, q2.v));
}

template <typename T, typename U>
auto operator*(const U& value, const Quaternion<U>& q2) {
    return Quaternion<std::common_type_t<T, U>(q2.v * value, q2.s * value);
}

template <typename T, typename U>
auto operator*(const Quaternion<U>& q2, const U& value) {
    return value * q2;
}

template <typename T, typename U>
auto operator/(const Quaternion<U>& q2, const U& value) {
    return Quaternion<std::common_type_t<T, U>(q2.v / value, q2.s / value);
}

template <typename T, typename U>
auto Dot(const Quaternion<T>& q1, const Quaternion<T>& q2) {
    return Dot(q1.v, q2.v) + q1.s * q2.s;
}

template <typename T, typename U>
auto operator+(const Quaternion<T>& q1, const Quaternion<U>& q2) {
    return Quaternion<std::common_type_t<T, U>(q1.v + q2.v, q1.s + q2.s);
}

template <typename T, typename U>
auto operator-(const Quaternion<T>& q1, const Quaternion<U>& q2) {
    return Quaternion<std::common_type_t<T, U>(q1.v - q2.v, q1.s - q2.s);
}

template <typename T>
auto Length2(const Quaternion<T>& q) {
    return Length2(q.v) + q.s * q.s;
}

template <typename T>
auto Length(const Quaternion<T>& q) {
    return std::sqrt(Length2(q));
}

template <typename T>
auto Conjugate(const Quaternion<T>& q) {
    return Quaternion<T>(-q.v, q.s);
}

template <typename T>
auto Inverse(const Quaternion<T>& q) {
    return Conjugate(q) / Dot(q, q);
}

template <typename T>
auto Normalize(const Quaternion<T>& q) {
    return q / Length(q);
}

}
