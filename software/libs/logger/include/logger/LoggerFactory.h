#ifndef LOGGERFACTORY_H
#define LOGGERFACTORY_H

#include <memory>
#include <string>

#include "spdlog/spdlog.h"

class LoggerFactory {
   public:
    LoggerFactory() = default;

    static std::shared_ptr<spdlog::logger> registerOrGetLogger(
        const std::string &logger_name,
        spdlog::level::level_enum logger_level);
};

#endif  // LOGGERFACTORY_H