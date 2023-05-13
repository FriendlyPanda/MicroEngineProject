

#include "Game/Nodes/NodeSystem.h"
#include "Game/Graphics/GE.h"
#include <iostream>
#include "Game/Graphics/GE.cpp"

/**
 * simple multi sink logger to log to the file and
 * @param name
 * @return
 */
spdlog::logger getLogger(string name){
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

    spdlog::logger logger(name, {console_sink, file_sink});
    return logger;
}

int main(int argc, char * args[]) {

    auto logger = getLogger("Graphics Engine");

    GraphicsEngine ge(logger);

    ge._init();
    ge._run();
    ge._close();

    return 0;
}
