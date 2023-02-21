//
// Created by JFH on 03/01/2023.
//

#include <cmath>
#include "GE.h"
#include "../Nodes/Node.h"


GraphicsEngine::GraphicsEngine() {
    geWindow = nullptr;
    //geTexture = new NodeSprite();
    geRenderer = nullptr;
    exit = false;
    imgFlags = IMG_INIT_PNG;
    gc = nullptr;
}

int GraphicsEngine::_execute() {

    if(_init() != 0){
        return -1;
    }

    NodeSprite newTexture = NodeSprite();
    SDL_Point scale;
    scale.x = 320;
    scale.y = 240;
    ((Node*) newTexture.getHost())->setConfig(gc);
    newTexture.loadTexture("Assets/Err.png",4,3,2,scale);

    //geTexture = &newTexture;

    Uint64 start;
    Uint64 end;
    Uint64 animationTrigger = 0;
    while(!exit){

         start = SDL_GetPerformanceCounter();

         if(animationTrigger <= start){
             animationTrigger = start + 20000*(1000/GAME_SPEED);
             //geTexture->nextFrame();
         }

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                exit = true;
            }
        }


        _render();

         end = SDL_GetPerformanceCounter();

        float frameRate = (float)(end - start) / (float)SDL_GetPerformanceFrequency(); // get the ms
        printf("FPS: %f\n", (1.0f/frameRate));
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
    //geTexture = nullptr;
    geRenderer = nullptr;
    exit = false;
    imgFlags = IMG_INIT_PNG;
    gc = gameConfig;
}
