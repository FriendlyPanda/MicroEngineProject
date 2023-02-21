//
// Created by JFH on 08/01/2023.
//
#include "GE.h"

int GraphicsEngine::_init() {

    //initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize.SDL_ERROR: %s", SDL_GetError());
        _close();
        return -1;
    }
    // create window
    geWindow = SDL_CreateWindow("SDL_WINDOW", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(geWindow == nullptr){
        printf("Could not create a window. SDL_ERROR: %s", SDL_GetError());
        _close();
        return -1;
    }

    //create renderer
    geRenderer = SDL_CreateRenderer(geWindow, -1, SDL_RENDERER_ACCELERATED);
    if(geRenderer == nullptr){
        printf("Could not create a renderer. SDL_ERROR: %s", SDL_GetError());
        _close();
        return -1;
    }else{
        SDL_SetRenderDrawColor(geRenderer, 0xff,0xff,0xff,0x00);
        gc->set(RENDER , geRenderer);
    }

    // initialize SDL_Image
    if( !(IMG_Init(imgFlags) & imgFlags)){
        printf("Could not initialize sdl_imgae.\nSDL_Image_ERROR: %s", IMG_GetError());
        _close();
        return -1;
    }
    return 0;
}