//
// Created by adamh on 14/01/2023.
//

#ifndef MEP_GAMEOBJECT_H
#define MEP_GAMEOBJECT_H



#include "SDL.h"
#include "GameNode.h"

class GameObject: GameNode {
public:
    virtual int init() = 0;
    void setTexture();
    void setID();
    void step();
    void draw();
private:
    unsigned int ID;
    SDL_Rect dimensionAndCoords;
    SDL_Rect collision;
    SDL_Texture * sprite;


};


#endif //MEP_GAMEOBJECT_H
