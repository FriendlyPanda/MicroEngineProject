//
// Created by adamh on 17/01/2023.
//

#ifndef MEP_GAMESPRITE_H
#define MEP_GAMESPRITE_H


#include <string>
#include "SDL.h"
#include <SDL_image.h>
#include "GameNode.h"

/**
 * Sprite node inheriting from GameNode
 * this node holds graphical information for the objects, it is not required for an object to have a sprite,
 * but all sprites require parents.
 */
class GameSprite:public GameNode{
private:
    SDL_Texture * gTexture;
    float spriteAnimationSpeed = 1;
    unsigned int frame = 0;
    unsigned int numberOfFrames = 0;
    clock_t frameTimer; // used for determining how fast to change the frames.
    SDL_Rect * frames;
    SDL_Point dimentions;
public:
    GameSprite();
    GameSprite(SDL_Texture *gTexture);
    SDL_Texture * loadTexture(const std::string& path, int numbOfFrames, int numbOfFramesVer, int numbOfFramesHor, SDL_Point frameSize);
    unsigned int getTextureWidth();
    unsigned int getTextureHeight();
    unsigned int getWidth();
    unsigned int getHeight();
    [[nodiscard]] unsigned int getCurrentFrame() const;
    void setFrame(int frameIndex);
    [[nodiscard]] unsigned int getNumberOfFrames() const;
    void render();
    ~GameSprite();
    void free();
    void setSpeed(float speed);
private:
    static SDL_Point getsize(SDL_Texture *texture);
};


#endif //MEP_GAMESPRITE_H
