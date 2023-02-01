//
// Created by JFH on 03/01/2023.
//

#include <cmath>
#include "GE.h"


GraphicsEngine::GraphicsEngine() {
    geWindow = nullptr;
    geTexture = new GameSprite();
    geRenderer = nullptr;
    exit = false;
    imgFlags = IMG_INIT_PNG;
    gc = nullptr;
}

int GraphicsEngine::_execute() {

    if(_init() != 0){
        return -1;
    }

    GameSprite newTexture = GameSprite();
    SDL_Point scale;
    scale.x = 32;
    scale.y = 32;
    newTexture.setConfig(gc);
    newTexture.loadTexture("Assets/Err.png",4,2,2,scale);
    newTexture.setSpeed(0.1);

    geTexture = &newTexture;

    while(!exit){

        Uint64 start = SDL_GetPerformanceCounter();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                exit = true;
            }
        }

        _render();

        Uint64 end = SDL_GetPerformanceCounter();

        float elapsedMS = (float)(end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f; // get the ms
        SDL_Delay(std::floor((1000.0f/((float)*gc->get<int>(GAME_SPEED))) - elapsedMS));
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
