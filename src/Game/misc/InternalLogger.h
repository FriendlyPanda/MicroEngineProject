//
// Created by jan on 5/25/23.
//

#ifndef MEP_INTERNALLOGGER_H
#define MEP_INTERNALLOGGER_H

#include "../../properties/MessageBoard.h"
#include "spdlog/include/spdlog/spdlog.h"

class InternalLogger {
public:
    MessageBoard * msg;
    spdlog::logger logger = spdlog::logger("");

    explicit InternalLogger(std::string logger_name);
    void clear();

};


#endif //MEP_INTERNALLOGGER_H
