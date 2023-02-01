//
// Created by JFH on 08/01/2023.
//
#include "GE.h"

int GraphicsEngine::_init() {

    //initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
#ifndef NDEBUG
        spdlog::error("SDL could not initialize.SDL_ERROR: {0}", SDL_GetError());
#endif
        _close();
        return -1;
    }
    // create window
    geWindow = SDL_CreateWindow("SDL_WINDOW", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(geWindow == nullptr){
#ifndef NDEBUG
        spdlog::error("Could not create a window. SDL_ERROR: {0}", SDL_GetError());
#endif
        _close();
        return -1;
    }

    //create renderer
    geRenderer = SDL_CreateRenderer(geWindow, -1, SDL_RENDERER_ACCELERATED);
    if(geRenderer == nullptr){
#ifndef NDEBUG
        spdlog::error("Could not create a renderer. SDL_ERROR: {0}", SDL_GetError());
#endif
        _close();
        return -1;
    }else{
        SDL_SetRenderDrawColor(geRenderer, 0xff,0xff,0xff,0x00);
        gc->set(RENDER , geRenderer);
    }

    // initialize SDL_Image
    if( !(IMG_Init(imgFlags) & imgFlags)){
#ifndef NDEBUG
        spdlog::error("Could not initialize sdl_imgae.\nSDL_Image_ERROR: {0}", IMG_GetError());
#endif
        _close();
        return -1;
    }
    return 0;
}