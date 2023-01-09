//
// Created by adamh on 08/01/2023.
//
#include "GE.h"

int GraphicsEngine::_init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("ERROR:\tSDL could not initialize.\nSDL_ERROR: %s\n", SDL_GetError());
        return -1;
        _close();
    }
    geWindow = SDL_CreateWindow("SDL_WINDOW", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(geWindow == nullptr){
        printf("ERROR:\tCould not create a window.\nSDL_ERROR: %s\n", SDL_GetError());
        return -1;
        _close();
    }

    //Get window surface
    geScreenSurface = SDL_GetWindowSurface(geWindow);

    return 0;
}