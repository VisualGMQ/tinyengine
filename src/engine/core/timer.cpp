#include "engine/core/timer.hpp"

namespace engine {

std::unordered_map<unsigned int, Timer> Timer::timers_;
unsigned int Timer::curID_ = 0;
double Timer::sElapse_ = 0;
double Timer::sTime_ = 0;

double Timer::GetTime() {
    return glfwGetTime();
}

double Timer::GetElapse() {
    return sElapse_;
}

void Timer::UpdateElapse() {
    sElapse_ = glfwGetTime() - sTime_;
    sTime_ = glfwGetTime();
}

void Timer::UpdateTimers() {
    for (auto& [id, timer] : timers_) {
        timer.Update();
    }
}

TimerID Timer::AddTimer(Timer::Callback callback, double time, void* param) {
    TimerID id = curID_++;
    timers_.emplace(std::piecewise_construct,
                    std::forward_as_tuple(id),
                    std::forward_as_tuple(id, callback, time, param));
    return id; 
}

void Timer::RemoveTimer(unsigned int id) {
    auto it = timers_.find(id);
    if (it != timers_.end()) {
        it->second.shouldDie_ = true;
    }
}

void Timer::CleanUpTimers() {
    auto it = timers_.begin();
    while (it != timers_.end()) {
        if (it->second.shouldDie_) {
            timers_.erase(it);
            it = timers_.begin();
        } else {
            it ++;
        }
    }
}


Timer::Timer(TimerID id, Callback callback, double time, void* param): id_(id), callback_(callback), elapse_(0), time_(time), param_(param) {}

void Timer::Update() {
    elapse_ += Timer::GetElapse();
    while (elapse_ >= time_) {
        elapse_ -= time_;
        if (callback_) {
            time_ = callback_(*this, time_, param_);
        }
    }
}

}