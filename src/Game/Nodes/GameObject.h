//
// Created by adamh on 14/01/2023.
//

#ifndef MEP_GAMEOBJECT_H
#define MEP_GAMEOBJECT_H

#include "SDL.h"
#include "NodeEmpty.h"
#include "NodeSprite.h"
#include "../misc/GameMisc.h"

class GameObject{
    /** object ID will be used when there are multiple instances of the same object */
    unsigned int objectID;
    NodeEmpty * objNode;
    NodeSprite * objTexture;
    GameObject * parent;
    SDL_Rect * positionAndDimention;
    float angle = 0; // gonna use radians lol, 0 rad is right

public:
    GameObject();
    void render();
    void setPos(int x, int y);
    int * x();
    int * y();
    SDL_Point getPos();
    void setObjectID(unsigned int newObjectID);
    unsigned int getObjectID();
    void nextFrame();
    void setNode(NodeEmpty * node);

    ~GameObject();
};


#endif //MEP_GAMEOBJECT_H