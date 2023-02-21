//
// Created by adamh on 17/01/2023.
//

#ifndef MEP_NODESPRITE_H
#define MEP_NODESPRITE_H


#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "NodeEmpty.h"

/**
 * Sprite objNode inheriting from NodeEmpty
 * this objNode holds graphical information for the objects, it is not required for an object to have a sprite,
 * but all sprites require parents.
 */
class NodeSprite : public NodeEmpty{
private:
    SDL_Texture * gTexture;
    unsigned int frame = 0;
    unsigned int numberOfFrames = 0;
    SDL_Rect * frames;
    SDL_Point dimentions{};
public:
    NodeSprite();
    NodeSprite(SDL_Texture *gTexture);
    SDL_Texture * loadTexture(const std::string& path, int numbOfFrames, int numbOfFramesVer, int numbOfFramesHor, SDL_Point frameSize);
    unsigned int getTextureWidth() const;
    unsigned int getTextureHeight() const;
    unsigned int getWidth();
    unsigned int getHeight();
    [[nodiscard]] unsigned int getCurrentFrame() const;
    void setFrame(int frameIndex);
    [[nodiscard]] unsigned int getNumberOfFrames() const;
    void render(SDL_Rect * pos);
    ~NodeSprite();
    void free();
    void setSpeed(float speed);
    void nextFrame();
    const std::type_info & getType(){
        return typeid(this);
    }
private:
    static SDL_Point getsize(SDL_Texture *texture);
};


#endif //MEP_NODESPRITE_H
