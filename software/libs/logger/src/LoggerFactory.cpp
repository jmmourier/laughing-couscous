#include "logger/LoggerFactory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <regex>

std::shared_ptr<spdlog::logger> LoggerFactory::registerOrGetLogger(
    const std::string &logger_name,
    spdlog::level::level_enum logger_level) {
    auto logger = spdlog::get(logger_name);

    if (logger) {
        logger->set_level(logger_level);
        return logger;
    }

    // Create static sinks to have them only created once and shared between loggers
    static auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    std::vector<spdlog::sink_ptr> sinks{stdout_sink};

    const auto *log_file = LOG_DIR "couscous.log";
    static auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file);
    sinks.push_back(file_sink);

    // Create combined logger
    logger = std::make_shared<spdlog::logger>(logger_name, sinks.begin(), sinks.end());

    spdlog::register_logger(logger);

    // reference: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
    static std::string std_pattern_format = "[%Y-%m-%dT%H:%M:%S.%f][%n][%l][%s:%#] %v";
    logger->set_pattern(std_pattern_format);

    logger->set_level(logger_level);

    return logger;
}
