#pragma once
#include <cstdint>
#include <string_view>

enum class MsgType : uint16_t {
    Error,
    Undefined,
    Game
};

class Logger {
    std::string get_current_time_formatted(const MsgType id);
    public:
    void print_log(const std::string_view message, const MsgType id = MsgType::Undefined);
    static Logger &instance();
    private:
    Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
};
