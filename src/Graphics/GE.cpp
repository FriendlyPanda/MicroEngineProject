//
// Created by JFH on 03/01/2023.
//

#include "GE.h"

GraphicsEngine::GraphicsEngine() {
    geWindow = nullptr;
    geTexture = nullptr;
    geRenderer = nullptr;
    exit = false;
    imgFlags = IMG_INIT_PNG;
    gc = nullptr;
}

int GraphicsEngine::_execute() {

    if(_init() != 0){
        return -1;
    }

    geTexture = loadTexture("Assets/Err.png");



    while(!exit){

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                exit = true;
            }
        }

        _render();
    }

    _close();
    return 0;
}

SDL_Texture * GraphicsEngine::loadTexture(std::string path) {
    SDL_Texture * finalTexture = IMG_LoadTexture(geRenderer, path.c_str());
    if(finalTexture == nullptr){
        printf("ERROR:\t\tCould not create texture.\nSDL_ERROR: %s\n", SDL_GetError());
    }

    return finalTexture;
}

GraphicsEngine::GraphicsEngine(GameConfiguration * gameConfig) {
    geWindow = nullptr;
    geTexture = nullptr;
    geRenderer = nullptr;
    exit = false;
    imgFlags = IMG_INIT_PNG;
    gc = gameConfig;
}
