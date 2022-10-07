#pragma once

namespace engine {

template <typename T>
class Cacher final {
public:
    virtual ~Cacher() = default;

    bool IsChanged() const { return isChanged_; }
    void ClearChangeState() { isChanged_ = false; }

    template <typename U>
    Cacher& operator=(const U& value) {
        Set(value);
    }

    T& operator*() {
        return data_;
    }

    T& operator->() {
        return data_;
    }

    template <typename U>
    void Set(const U& value) {
        if (data_ != value) {
            data_ = value;
            isChanged_ = true;
        }
    }

private:
    T data_;
    bool isChanged_ = true;
};

}