//
// Created by adamh on 03/01/2023.
//

#include "GE.h"

GraphicsEngine::GraphicsEngine() {
    geWindow = nullptr;
    geScreenSurface = nullptr;
    geCurrentSurface = nullptr;
    exit = false;
}

int GraphicsEngine::_execute() {

    if(_init() != 0){
        return -1;
    }

    geCurrentSurface = SDL_LoadBMP("Assets/Hello.bmp");
    if(geCurrentSurface == nullptr){
        printf("ERROR:\tCould not load image\nSDL_ERROR: %s\n", SDL_GetError());
        _close();
        return -1;
    }
    SDL_BlitSurface(geCurrentSurface, nullptr, geScreenSurface, nullptr);
    SDL_UpdateWindowSurface(geWindow);

    while(!exit){
        _render();
    }

    _close();
    return 0;
}
