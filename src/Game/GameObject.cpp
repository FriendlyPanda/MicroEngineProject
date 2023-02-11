//
// Created by adamh on 14/01/2023.
//

#include "GameObject.h"

/**
 * A simple constructor
 */
GameObject::GameObject() {
    objectID = 0;
    objNode = nullptr;
    objTexture = nullptr;
    parent = nullptr;
    *positionAndDimention = sdlRect(0,0,0,0);
}

void GameObject::render() {
    if(objTexture != nullptr){
        objTexture->render(positionAndDimention);
    }
}

void GameObject::setPos(int x, int y) {
    positionAndDimention->x = x;
    positionAndDimention->y = y;
}

int *GameObject::x() {
    return &positionAndDimention->x;
}

int *GameObject::y() {
    return &positionAndDimention->y;
}

SDL_Point GameObject::getPos() {
    return sdlPoint(positionAndDimention->x, positionAndDimention->y);
}

void GameObject::setObjectID(unsigned int newObjectID) {
    objectID = newObjectID;
}

unsigned int GameObject::getObjectID() {
    return objectID;
}

void GameObject::nextFrame() {
    if(objTexture != nullptr){
        objTexture->nextFrame();
    }
}

GameObject::~GameObject() {
    objNode = nullptr;
    objTexture = nullptr;
    parent = nullptr;
    delete positionAndDimention;
    positionAndDimention = nullptr;
}

void GameObject::setNode(GameNode *node) {
    objNode = node;

}


