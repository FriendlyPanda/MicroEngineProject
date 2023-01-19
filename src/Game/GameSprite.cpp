//
// Created by adamh on 17/01/2023.
//

#include "GameSprite.h"

GameSprite::GameSprite(){
    gTexture = nullptr;
    gTWidth = 0;
    gTHeight = 0;
}

SDL_Texture *GameSprite::loadTexture(std::string path) {
    free();
    /*

    SDL_Texture * finalTexture = IMG_LoadTexture(geRenderer, path.c_str());
    if(finalTexture == nullptr){
        printf("ERROR:\t\tCould not create texture.\nSDL_ERROR: %s\n", SDL_GetError());
    }
     */

    return nullptr;
}

unsigned int GameSprite::getWidth() {
    return gTWidth;
}

GameSprite::~GameSprite() {
    free();
}

unsigned int GameSprite::getHeight() {
    return gTHeight;
}

void GameSprite::free() {

}
