//
// Created by adamh on 17/01/2023.
//

#ifndef MEP_GAMESPRITE_H
#define MEP_GAMESPRITE_H


#include <string>
#include "SDL.h"

class GameSprite {
private:
    SDL_Texture * gTexture;
    unsigned int gTWidth;
    unsigned int gTHeight;
public:
    GameSprite();

    GameSprite(SDL_Texture *gTexture, unsigned int gTWidth, unsigned int gTHeight);

    SDL_Texture * loadTexture(std::string path);
    unsigned int getWidth();
    unsigned int getHeight();
    ~GameSprite();
    void free();
};


#endif //MEP_GAMESPRITE_H
