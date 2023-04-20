//
// Created by JFH on 08/01/2023.
//
#include "GE.h"

int GraphicsEngine::_render() {

    SDL_RenderClear(geRenderer);
    for(int xx = 0; xx < DEFAULT_SCREEN_WIDTH; xx++){
        for(int yy = 0; yy < DEFAULT_SCREEN_HEIGHT; yy++){
            SDL_SetRenderDrawColor(geRenderer, min(xx/2, 255),  min(yy/2, 255), 255, 255);
            SDL_RenderDrawPoint(geRenderer, xx, yy);
        }
    }



    SDL_RenderPresent(geRenderer);
    return 0;
}