//
// Created by adamh on 14/01/2023.
//

#ifndef MEP_GAMEOBJECT_H
#define MEP_GAMEOBJECT_H



#include "SDL.h"
#include "GameNode.h"
#include "GameSprite.h"
#include "GameMisc.h"

class GameObject{
    unsigned int objectID;
    GameNode * objNode;
    GameSprite * objTexture;
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
    void setNode(GameNode * node);

    ~GameObject();
};


#endif //MEP_GAMEOBJECT_H
