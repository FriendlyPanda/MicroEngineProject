//
// Created by jan on 5/25/23.
//

#include "InternalLogger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

InternalLogger::InternalLogger(std::string logger_name) {

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
    file_sink->set_level(spdlog::level::trace);

#ifdef NDEBUG
    logger = spdlog::logger(std::move(logger_name), {file_sink});
#else
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[%H:%M:%S %z] [debug] [%^%l%$] %v");

    logger = spdlog::logger(std::move(logger_name), {console_sink, file_sink});
#endif

//    msg = new MessageBoard("Assets/properties/sys_graphics_en.properties");
}

void InternalLogger::clear() {
    free(msg);
    msg = nullptr;
}

void InternalLogger::setMessageBoard(MessageBoard * newMSG) {
    this->msg = newMSG;
}

MessageBoard *InternalLogger::getMessageBoard() {
    return msg;
}

void InternalLogger::setupMessageBoard(const std::string& filepath) {
    this->msg = new MessageBoard(filepath);
}

#ifdef NDEBUG
// release version
#else
//debug version
void InternalLogger::debug(const std::string& message) {
    logger.debug(message);
}

void InternalLogger::debugMsg(const std::string& msgKey) {
    logger.debug(msg->get(msgKey));
}

void InternalLogger::debugMsg(const std::string& msgKey, const std::vector<std::string> &params) {
    logger.debug(msg->get(msgKey, params));
}
#endif

void InternalLogger::error(const std::string& message) {
    logger.error(message);
}

void InternalLogger::errorMsg(const std::string& msgKey) {
    logger.error(msg->get(msgKey));
}

void InternalLogger::errorMsg(const std::string& msgKey, const std::vector<std::string> &params) {
    logger.error(msg->get(msgKey, params));
}

void InternalLogger::warning(const std::string& message) {
    logger.warn(message);
}

void InternalLogger::warningMsg(const std::string& msgKey) {
    logger.warn(msg->get(msgKey));
}

void InternalLogger::warningMsg(const std::string& msgKey, const std::vector<std::string> &params) {
    logger.warn(msg->get(msgKey, params));
}

void InternalLogger::info(const std::string& message) {
    logger.info(message);
}

void InternalLogger::infoMsg(const std::string& msgKey) {
    logger.info(msg->get(msgKey));
}

void InternalLogger::infoMsg(const std::string& msgKey, const std::vector<std::string> &params) {
    logger.info(msg->get(msgKey, params));
}
