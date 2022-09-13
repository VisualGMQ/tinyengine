#pragma once

#include "engine/core/pch.hpp"

namespace engine {


class DLLEXPORT Timer final {
public:
    struct Param {
        void* userParam;
        Timer* owner;
    };

    using Callback = std::function<uint32_t(Timer&, uint32_t, void*)>;

    static Timer* AddTimer(Callback, uint32_t time, void* param);
    static void RemoveTimer(SDL_TimerID);
    static uint64_t GetTime();
    static uint64_t GetElapse();
    static void UpdateElapse();

    Timer() = default;
    Timer(Callback, uint32_t, void*);
    ~Timer();
    void Update();
    SDL_TimerID ID() const { return id_; }

    uint32_t Interval() const { return interval_; }

    Callback GetCallback() const { return callback_; }

    void Start();
    void Stop();

private:
    Callback callback_;
    Param param_;
    uint32_t interval_;
    SDL_TimerID id_;

    static Uint32 myCallback(Uint32 interval, void *param);
    static std::unordered_map<SDL_TimerID, std::unique_ptr<Timer>> timerMap_;

    static uint64_t sElapse_;
    static uint64_t sTime_;
};

}