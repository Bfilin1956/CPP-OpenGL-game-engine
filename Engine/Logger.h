#pragma once
#include <chrono>

#include <iostream>
#include <string>


namespace Log {
    enum class MsgType : uint16_t {
        Error,
        Undefined,
        Game
    };

    inline std::string get_current_time_formatted(const Log::MsgType id) {
        const auto now = std::chrono::system_clock::now();
        auto now_time = std::chrono::system_clock::to_time_t(now);

        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        std::tm tm{};

#ifdef _WIN32
        localtime_s(&tm, &now_time);
#else
        localtime_r(&now_time, &tm);
#endif

        if (id == Log::MsgType::Error)
            return std::format("[ERROR {:02}:{:02}:{:02}.{:03}] ",
                tm.tm_hour, tm.tm_min, tm.tm_sec, ms.count());
        return std::format("[{:02}:{:02}:{:02}.{:03}] ",
            tm.tm_hour, tm.tm_min, tm.tm_sec, ms.count());
    }

    namespace Color {
        const std::string RED = "\033[31m";
        const std::string GREEN = "\033[32m";
        const std::string YELLOW = "\033[33m";
        const std::string BLUE = "\033[34m";
        const std::string MAGENTA = "\033[35m";
        const std::string CYAN = "\033[36m";
        const std::string WHITE = "\033[37m";
        const std::string UNDERLINE_GREEN = "\033[4;32m";
        const std::string UNDERLINE_YELLOW = "\033[4;33m";

        const std::string BRIGHT_BLACK   = "\033[90m";
        const std::string BRIGHT_RED     = "\033[91m";
        const std::string BRIGHT_GREEN   = "\033[92m";
        const std::string BRIGHT_YELLOW  = "\033[93m";
        const std::string BRIGHT_BLUE    = "\033[94m";
        const std::string BRIGHT_MAGENTA = "\033[95m";
        const std::string BRIGHT_CYAN    = "\033[96m";
        const std::string BRIGHT_WHITE   = "\033[97m";

        const std::string BG_RED = "\033[41m";
        const std::string BG_GREEN = "\033[30;42m";
        const std::string BG_YELLOW = "\033[30;43m";
        const std::string BG_BLUE = "\033[44m";
        const std::string BG_MAGENTA = "\033[45m";
        const std::string BG_CYAN = "\033[30;46m";
        const std::string BG_WHITE = "\033[30;47m";

        const std::string RESET = "\033[0m";
        const std::string BOLD = "\033[1m";
        const std::string UNDERLINE = "\033[4m";
        const std::string INVERSE = "\033[7m";
    }

    inline void print_log(const std::string_view message,
                          const Log::MsgType id = MsgType::Undefined,
                          const std::string_view word_color = Log::Color::RESET,
                          const std::string_view bg_color = Log::Color::RESET) {
        //if (LOG_LEVEL == LogLevel::none) return;
        if (id == Log::MsgType::Error) {
            std::cout << Log::get_current_time_formatted(id)<<
                    Log::Color::RED << message << Log::Color::RESET << "\n";
            return;
        }
        std::cout << Log::get_current_time_formatted(id)<< bg_color<<
            word_color << message << Log::Color::RESET << Log::Color::RESET << "\n";
    }
}