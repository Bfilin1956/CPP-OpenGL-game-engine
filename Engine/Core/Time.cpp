//
// Created by filin on 8/13/26.
//

#include "Time.h"

void Time::update() {
    const auto now = Clock::now();
    deltaTime_ = std::chrono::duration<float>( now - lastTime_ ).count();
    lastTime_ = now;
}

float Time::deltaTime() const {
    return deltaTime_;
}

Time &Time::instance() {
    static Time inst;
    return inst;
}
