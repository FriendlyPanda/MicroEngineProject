//
// Created by JFH on 03/01/2023.
//

#include <cmath>
#include <utility>
#include "GE.h"
#include "../Nodes/Node.h"


GraphicsEngine::GraphicsEngine() {
    geWindow = nullptr;
    //geTexture = new NodeSprite();
    geRenderer = nullptr;
    exit = false;
    imgFlags = IMG_INIT_PNG;
    gc = nullptr;
    nodeSys = nullptr;
}

int GraphicsEngine::_execute() {

    /*
    NodeSprite newTexture = NodeSprite();
    SDL_Point scale = sdlPoint(8,8);
    nodeSys->add(nodeSys->getHeadNode()->getName(),&newTexture,"sprite3");
    newTexture.loadTexture("Assets/basicSet.bmp",10,2,5,scale);

    nodeSys->getNodesOfType(&spriteList);
    */
    Uint64 start;
    Uint64 end;
    Uint64 animationTrigger = 0;
    while(!exit){

         start = SDL_GetPerformanceCounter();

         if(animationTrigger <= start){
             animationTrigger = start + 10000*(1000/ *(gc->get<int>(GAME_SPEED)));
             for(NodeSprite * sprite: spriteList){
                 sprite->nextFrame();
             }
         }

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                exit = true;
            }
        }


        _render();

         end = SDL_GetPerformanceCounter();

        tempFPS = (int)((float)(end - start) / (float)SDL_GetPerformanceFrequency()); // get the ms
        //printf("FPS: %f\n", (1.0f/frameRate));
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

GraphicsEngine::GraphicsEngine(GameConfiguration * gameConfig, std::vector<NodeSprite *> newSpriteList) {
    geWindow = nullptr;
    geRenderer = nullptr;
    exit = false;
    imgFlags = IMG_INIT_PNG;
    nodeSys = nullptr;
    spriteList = std::move(newSpriteList);
    gc = gameConfig;
}

GraphicsEngine::GraphicsEngine(GameConfiguration *gameConfig) {
    geWindow = nullptr;
    geRenderer = nullptr;
    exit = false;
    nodeSys = nullptr;
    imgFlags = IMG_INIT_PNG;
    gc = gameConfig;
}

void GraphicsEngine::setNodeSystem(NodeSystem * newNodeSystem) {
    nodeSys = newNodeSystem;
}

Uint8 GraphicsEngine::min(int a, int b) {
    if(a < b){
        return a;
    }else{
        return b;
    }
}
