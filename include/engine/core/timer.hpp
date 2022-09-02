#pragma once

#include "engine/core/pch.hpp"

namespace engine {

class Timer final {
public:
    using Callback = std::function<double(double, void*)>;

    static unsigned int AddTimer(Callback, double time, void* param);
    static void RemoveTimer(unsigned int);
    static double GetTime();
    static double GetElapse();
    static void UpdateElapse();
    static void UpdateTimers();

    Timer() = default;
    Timer(Callback callback, double, void*);
    void Update();

private:
    double elapse_;
    double time_;
    Callback callback_;
    void* param_;

    static std::unordered_map<unsigned int, Timer> timers_;
    static unsigned int curID_;
    static double sElapse_;
    static double sTime_;
};

}