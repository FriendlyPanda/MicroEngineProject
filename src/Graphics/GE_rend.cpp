//
// Created by JFH on 08/01/2023.
//
#include "GE.h"

int GraphicsEngine::_render() {

    SDL_RenderClear(geRenderer);
    geTexture->render();
    SDL_RenderPresent(geRenderer);
    return 0;

}