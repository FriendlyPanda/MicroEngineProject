//
// Created by Jan F H on 14/01/2023.
//

#include "GameObject.h"

/**
 * A simple constructor
 */
GameObject::GameObject() {
    objectID = 0;
    objNode = nullptr;
    parent = nullptr;
    *positionAndDimention = rect(0, 0, 0, 0);
}


/**
 * set the position of the object
 * @param x the origin co-ordinate of the object
 * @param y the dimensions co-ordinate of the object
 */
void GameObject::setPos(float x, float y) {
    *positionAndDimention->getOrigin().X() = x;
    *positionAndDimention->getOrigin().Y() = y;
}

/**
 * return the pointer to the origin parameter
 * @return pointer to the origin
 */
float *GameObject::x() {
    return positionAndDimention->getOrigin().X();
}

/**
 * return the pointer to the dimensions parameter
 * @return pointer to the dimensions
 */
float *GameObject::y() {
    return positionAndDimention->getOrigin().Y();
}

/**
 * get the position of the object
 * @return
 */
O_Point GameObject::getPos() {
    return positionAndDimention->getOrigin();
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
 * simple destructor
 */
GameObject::~GameObject() {
    objNode = nullptr;
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


