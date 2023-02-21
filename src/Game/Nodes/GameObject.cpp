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

/**
 * a simple render command to pass to the sprite node
 */
void GameObject::render() {
    if(objTexture != nullptr){
        objTexture->render(positionAndDimention);
    }
}

/**
 * set the position of the object
 * @param x the x co-ordinate of the object
 * @param y the y co-ordinate of the object
 */
void GameObject::setPos(int x, int y) {
    positionAndDimention->x = x;
    positionAndDimention->y = y;
}

/**
 * return the pointer to the x parameter
 * @return pointer to the x
 */
int *GameObject::x() {
    return &positionAndDimention->x;
}

/**
 * return the pointer to the y parameter
 * @return pointer to the y
 */
int *GameObject::y() {
    return &positionAndDimention->y;
}

/**
 * get the position of the object
 * @return
 */
SDL_Point GameObject::getPos() {
    return sdlPoint(positionAndDimention->x, positionAndDimention->y);
}

/**
 * set the object ID
 * @param newObjectID new object ID
 */
void GameObject::setObjectID(unsigned int newObjectID) {
    objectID = newObjectID;
}

/**
 * get the object ID
 * @return the object ID
 */
unsigned int GameObject::getObjectID() {
    return objectID;
}

/**
 * call the texture to set the frame to the next one
 */
void GameObject::nextFrame() {
    if(objTexture != nullptr){
        objTexture->nextFrame();
    }
}

/**
 * simple destructor
 */
GameObject::~GameObject() {
    objNode = nullptr;
    objTexture = nullptr;
    parent = nullptr;
    delete positionAndDimention;
    positionAndDimention = nullptr;
}

/**
 * set a node to copy th behaviour from
 * @param node node
 */
void GameObject::setNode(NodeEmpty *node) {
    objNode = node;

}


