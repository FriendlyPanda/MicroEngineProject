

#include "Graphics/GE.h"
#include "Game/GameConfiguration.h"





int main(int argc, char * args[]) {
    GameConfiguration gc;
    gc.clean();
    int gameSpeed = 10;
    gc.set(GAME_SPEED, &gameSpeed);

#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
// debug code
    spdlog::warn("Debug mode.");
    spdlog::info("Value for SCREEN_HEIGHT = {0}",SCREEN_HEIGHT);
    spdlog::info("Value for SCREEN_WIDTH = {0}",SCREEN_WIDTH);
    spdlog::info("Value for FILLER = {0}",FILLER);
    spdlog::info("Value for RENDER = {0}",RENDER);
#endif



    GraphicsEngine * ge = new GraphicsEngine(&gc);
    return ge->_execute();
}
