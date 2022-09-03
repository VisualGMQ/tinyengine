#pragma once

#include "engine/core/pch.hpp"

namespace engine {

using TimerID = unsigned int;

class Timer final {
public:
    using Callback = std::function<double(Timer&, double, void*)>;

    static TimerID AddTimer(Callback, double time, void* param);
    static void RemoveTimer(unsigned int);
    static double GetTime();
    static double GetElapse();
    static void UpdateElapse();
    static void UpdateTimers();
    static void CleanUpTimers();

    Timer() = default;
    Timer(TimerID id, Callback callback, double, void*);
    void Update();
    TimerID ID() const { return id_; }

private:
    double elapse_;
    double time_;
    Callback callback_;
    void* param_;
    bool shouldDie_ = false;
    TimerID id_;

    static std::unordered_map<unsigned int, Timer> timers_;
    static unsigned int curID_;
    static double sElapse_;
    static double sTime_;
};

}