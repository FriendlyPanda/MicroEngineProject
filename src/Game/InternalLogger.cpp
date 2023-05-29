//
// Created by jan on 5/25/23.
//

#include "InternalLogger.h"

InternalLogger::InternalLogger(string logger_name) {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

#ifdef NDEBUG
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[%H:%M:%S %z] [%^%l%$] %v");
#else
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[%H:%M:%S %z] [debug] [%^%l%$] %v");
#endif

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
    file_sink->set_level(spdlog::level::trace);

    logger = spdlog::logger(std::move(logger_name), {console_sink, file_sink});
    msg = new MessageBoard("Assets/properties/messages_en.properties");
}

void InternalLogger::clear() {
    free(msg);
    msg = nullptr;
}
