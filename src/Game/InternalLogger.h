//
// Created by jan on 5/25/23.
//

#ifndef MEP_INTERNALLOGGER_H
#define MEP_INTERNALLOGGER_H

#include "../properties/MessageBoard.h"
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

class InternalLogger {
public:
    MessageBoard * msg;
    spdlog::logger logger = spdlog::logger("");

    explicit InternalLogger(string logger_name);
    void clear();

};


#endif //MEP_INTERNALLOGGER_H
