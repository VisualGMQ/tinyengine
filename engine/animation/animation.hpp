#pragma once

#include "engine/core/vmath.hpp"
#include "engine/core/timer.hpp"

namespace engine {

template <typename T>
class KeyFrame final {
public:
    KeyFrame::KeyFrame(T data, int time): data_(data), time_(time) { }
    int Time() const { return time_; }
    void SetTime(int time) { time_ = time; }
    T& Data() { return data_; }
    const T& Data() const { return data_; }

private:
    T data_;
    int time_;
};

/*
Animation animation({
    KeyFrame<float>(3.0, 1200),
    KeyFrame<Vec2>(Vec2(1, 2), 2300),
});
*/

template <typename T>
class Animation final {
public:
    Animation(const std::initializer_list<KeyFrame<T>>& frames, const std::reference_wrapper<T>& attribute);
    ~Animation() = default;

    void Play();
    void Pause();
    void Stop();
    void Rewind();
    bool IsPlay() const { return isPlay_; }

    void Update();

    void SetLoop(int loop) { loop_ = loop; }

private:
    struct KeyFrameOrderByTime {
        bool operator()(const KeyFrame<T>& f1, const KeyFrame<T>& f2) const {
            return f1.Time() < f2.Time();
        }
    };

    std::vector<KeyFrame<T>> keyframes_;
    bool isPlay_ = false;
    uint32_t curTime_ = 0;
    uint32_t curFrameIdx_ = 0;
    std::reference_wrapper<T> attribute_;
    T initAttr_;
    int loop_ = 0;
};

template <typename T>
Animation<T>::Animation(const std::initializer_list<KeyFrame<T>>& frames, const std::reference_wrapper<T>& attribute)
: attribute_(attribute) {
    std::set<KeyFrame<T>, KeyFrameOrderByTime> keyframeSet(frames);
    for (auto& frame : keyframeSet) {
        keyframes_.push_back(frame);
    }
    initAttr_ = attribute.get();
}

template <typename T>
void Animation<T>::Play() {
    isPlay_ = true;
    Rewind();
}

template <typename T>
void Animation<T>::Pause() {
    isPlay_ = false;
}

template <typename T>
void Animation<T>::Stop() {
    Pause();
    Rewind();
}

template <typename T>
void Animation<T>::Rewind() {
    curTime_ = 0;
    curFrameIdx_ = 0;
}

template <typename T>
void Animation<T>::Update() {
    if (!IsPlay()) return;

    curTime_ += Timer::GetElapse();

    while (curFrameIdx_ < keyframes_.size() && 
           keyframes_[curFrameIdx_].Time() < curTime_) {
        Loge("time = {}", keyframes_[curFrameIdx_].Time());
        Loge("curTime_ = {}", curTime_);
        curFrameIdx_++;
    }

    if (curFrameIdx_ >= keyframes_.size()) {
        if (loop_ == -1 || loop_ > 0) {
            if (loop_ > 0) loop_ --;
            Rewind();
        } else {
            Pause();
            attribute_ = keyframes_.back().Data();
            return;
        }
    }

    const T& curAttr = keyframes_[curFrameIdx_].Data();
    T prevAttr = curFrameIdx_ == 0 ? initAttr_ : keyframes_[curFrameIdx_ - 1].Data();
    uint32_t curFrameTime = keyframes_[curFrameIdx_].Time(),
             prevFrameTime = curFrameIdx_ == 0 ? 0 : keyframes_[curFrameIdx_ - 1].Time();
    uint32_t deltaTime = curFrameTime - prevFrameTime;
    attribute_.get() = Lerp<T, T>(prevAttr, curAttr, (float)(curTime_ - prevFrameTime) / float(deltaTime));
}

}