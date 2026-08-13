#pragma once
#include <cstdint>
#include <string_view>

enum class MsgType : uint16_t {
    Error,
    Undefined,
    Game
};

class Logger {
    std::string get_current_time_formatted(MsgType id);
    public:
    void print_log(std::string_view message, MsgType id = MsgType::Undefined);

    static Logger &instance();
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
};
