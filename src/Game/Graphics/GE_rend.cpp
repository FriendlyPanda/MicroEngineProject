//
// Created by JFH on 08/01/2023.
//
#include "GE.h"

int GraphicsEngine::_render() {

    SDL_RenderClear(geRenderer);
    SDL_Rect rect = sdlRect(0,100,32,32);
    for(int i = 0; i < spriteList.size(); i++){
        for(int xx = 0; xx < ((DEFAULT_SCREEN_WIDTH/32)/3); xx++){
            for(int yy = 0; yy < (DEFAULT_SCREEN_HEIGHT/32); yy++){
                rect.x = xx * ((32*3) * i);
                rect.y = yy * (32);
                spriteList.at(i)->render(&rect);
            }
        }
    }
    SDL_RenderPresent(geRenderer);
    return 0;

}