//
// Created by filin on 8/12/26.
//
#include <format>
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>
#include "Logger.h"

Logger &Logger::instance() {
    static Logger inst;
    return inst;
}

std::string Logger::get_current_time_formatted(const MsgType id) {

    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);

    const auto ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()
        ) % 1000;

    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif

    if (id == MsgType::Error)
    {
        return std::format( "[ERROR {:02}:{:02}:{:02}.{:03}] ", tm.tm_hour, tm.tm_min, tm.tm_sec, ms.count() );
    }

    return std::format( "[{:02}:{:02}:{:02}.{:03}] ", tm.tm_hour, tm.tm_min, tm.tm_sec, ms.count() );
}

void Logger::print_log(const std::string_view message, const MsgType id) {
    if (id == MsgType::Error) {
        std::cout << get_current_time_formatted(id) << message << "\n";
        return;
    }
    std::cout << get_current_time_formatted(id)<< message << "\n";
}
