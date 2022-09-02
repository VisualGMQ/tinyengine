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

unsigned int Timer::AddTimer(Timer::Callback callback, double time, void* param) {
    unsigned int id = curID_++;
    timers_.emplace(std::piecewise_construct,
                    std::forward_as_tuple(id),
                    std::forward_as_tuple(callback, time, param));
    return id; 
}

void Timer::RemoveTimer(unsigned int id) {
    timers_.erase(id);
}


Timer::Timer(Callback callback, double time, void* param): callback_(callback), elapse_(0), time_(time), param_(param) {}

void Timer::Update() {
    elapse_ += Timer::GetElapse();
    while (elapse_ >= time_) {
        elapse_ -= time_;
        if (callback_) {
            time_ = callback_(time_, param_);
        }
    }
}

}