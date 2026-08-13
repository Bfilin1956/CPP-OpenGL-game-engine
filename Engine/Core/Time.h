#pragma once
#include <chrono>

class Time {
public:
    void update();

    [[nodiscard]] float deltaTime() const;

    static Time& instance();
    Time() = default;
    Time(const Time&) = delete;
    Time& operator=(const Time&) = delete;
    Time(Time&&) = delete;
    Time& operator=(Time&&) = delete;
private:
    using Clock = std::chrono::steady_clock;

    Clock::time_point lastTime_{Clock::now()};
    float deltaTime_{};
};