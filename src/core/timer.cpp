#include "engine/core/timer.hpp"

namespace engine {

uint64_t Timer::sElapse_ = 0;
uint64_t Timer::sTime_ = 0;
std::unordered_map<SDL_TimerID, std::unique_ptr<Timer>> Timer::timerMap_;

uint64_t Timer::GetTime() {
    return SDL_GetTicks64();
}

uint64_t Timer::GetElapse() {
    return sElapse_;
}

void Timer::UpdateElapse() {
    sElapse_ = GetTime() - sTime_;
    sTime_ = GetTime();
}

Uint32 Timer::myCallback(Uint32 interval, void *param) {
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = param;
    userevent.data2 = nullptr;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

Timer* Timer::AddTimer(Timer::Callback callback, uint32_t interval, void* param) {
    std::unique_ptr<Timer> timer = std::make_unique<Timer>(callback, interval, param);
    Timer* result = timer.get();
    SDL_TimerID id = timer->ID();
    timerMap_[id] = std::move(timer);
    return result;
}

void Timer::RemoveTimer(SDL_TimerID id) {
    timerMap_.erase(id);
}

Timer::Timer(Callback callback, uint32_t interval, void* param): callback_(callback), interval_(interval) {
    param_.owner = this;
    param_.userParam = param;
    id_ = SDL_AddTimer(interval, myCallback, (void*)&param_);
}

Timer::~Timer() {
    SDL_RemoveTimer(id_);
}

}