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
        if (list.size != W * H) {
            Loge("list.size != W * H");
        } else {
            for (int i = 0; i < H; i++) {
                for (int j = 0; j < W; j++) {
                    Get(j, i) = *(list.begin() + j * H + i);
                }
            }
        }
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
    return !(*this == o);
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
auto operator/(const Mat<T, W, H>& m, const U& value) {
    Mat<std::common_type_t<U, T>, W, H> result;
    for (int i = 0; i < W * H; i++) {
        result.data_[i] = m.data_[i] / value;
    }
    return result;
}

template <typename T, typename U, unsigned int W, unsigned int H>
auto operator*(const U& value, const Mat<U, W, H>& m2) {
    return m2 * value;
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
}


template <typename T>
class Mat<T, 1, 3> final {
public:
    Mat() {
        memset(data_, 0, sizeof(T) * 3);
    }

    Mat(T x, T y, T z) {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
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

using Vec3 = Mat<float, 1, 3>;


template <typename T>
class Mat<T, 1, 2> final {
public:
    Mat() {
        memset(data_, 0, sizeof(T) * 2);
    }

    Mat(T x, T y) {
        data_[0] = x;
        data_[1] = y;
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

    unsigned int Height() const { return 2; }
    unsigned int Width() const { return 1; }

    template <typename U>
    Mat& operator+=(const Mat<U, 1, 2>& o) {
        for (int i = 0; i < W * H; i++) {
            data_[i] += o.data_[i];
        }
        return *this;
    }

    template <typename U>
    Mat& operator-=(const Mat<U, 1, 2>& o) {
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
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
        data_[3] = w;
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
T Length(const Vec<T, N>& v) {
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += v(0, i) * v(0, i);
    }
    return std::sqrt(sum);
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

}