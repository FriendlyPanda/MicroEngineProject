//
// Created by janha on 01/02/2023.
//
#include "GameNode.h"

/**
 * basic constructor
 */
GameNode::GameNode() {
    nodeName = "node_nan";
    gc = nullptr;
    parent = nullptr;
    numbOfChildren = 0;
    children.resize(maxChildren);
}

/**
 * Set a new parent to the objNode.
 * @param newParent parent GameNode to set to.
 */
void GameNode::setParent(GameNode *newParent) {
    this->parent = newParent;
}

/**
 * add a child to the next available space, if no spaces are available, print out an error
 * @param newChild the child to insert
 */
bool GameNode::addChild(GameNode *newChild) {
    if(numbOfChildren != maxChildren){
        newChild->setParent(this);
        children[numbOfChildren] = newChild;
        numbOfChildren++;
        return true;
    }
    printf("WARNING: not enough space for children");
    return false;
}

/**
 * set a child at a indexed positionAndDimention.
 * @param index the index at which to put the child.
 * @param newChild the pointer to the new child.
 */
void GameNode::setChild(int index, GameNode *newChild) {
    children.assign(index, newChild);

    /*
    if(index >= 0 && index < maxChildren){
        if(index < numbOfChildren){
            delete (children[index]);
            children[index] = newChild;
        }else if(index >= numbOfChildren){
            addChild(newChild);
        }
    }
     */
}

/**
 * get a pointer to a child at specific index, if index is further than the number of children then return the last child
 * @param index  the positionAndDimention of the child
 * @return the pointer to the child objNode
 */
GameNode *GameNode::getChild(int index) {


    return children.at(index);
    if(index < numbOfChildren){
        return children[index];
    }else{
        return children[numbOfChildren - 1];
    }
}

/**
 * Get a list of children of the objNode
 * @return list of pointers to children nodes
 */
std::vector<GameNode *> GameNode::getChildren() {
    return children;
}

/**
 * check if the relative positioning has been set to TRUE or FALSE.
 * @return relative rotation
 */
bool GameNode::isRelativePosition() {
    return relativePosition;
}

/**
 * check if the relative rotation has been set to TRUE or FALSE.
 * @return relative rotation
 */
bool GameNode::isRelativeRotation() {
    return relativeRotation;
}

/**
 * sets whether to use relative positioning or not
 * @param pos the boolean to set the relative positioning.
 */
void GameNode::setRelativePosition(bool pos) {
    relativePosition = pos;
}

/**
 * sets whether to use relative rotation or not
 * @param rot the boolean to set the relative rotation.
 */
void GameNode::setRelativeRotation(bool rot) {
    relativeRotation = rot;
}

/**
 * Retrieves the config object pointer, if no pointer to an config object is set, the objNode asks the parent for the config object pointer, and sets it for itself.
 * The config object pointer can be set at any child objNode, and consequent child nodes will use the new config object pointer.
 * @return GameConfiguration [pointer]
 */
GameConfiguration *GameNode::getConfig() {
    if(gc == nullptr){
        if(parent == nullptr){
            return nullptr;
        }else{
            gc = parent->getConfig();
            return gc;
        }
    }else{
        return gc;
    }
}

/**
 * simple destructor
 */
GameNode::~GameNode() {
    parent = nullptr;
    gc = nullptr;
    freeChildren();
}



/**
 * Returns the parent of the objNode, if objNode doesn't have a parent, return null
 * @return GameNode parent
 */
GameNode *GameNode::getParent() {
    return parent;
}

/**
 * set the Game Configuration
 * @param newgc new GameConfiguration
 */
void GameNode::setConfig(GameConfiguration *newgc) {
    this->gc = newgc;
}


/**
 * set the ID of the objNode
 * @param newID new ID
 */
void GameNode::setNodeName(std::string newName) {
    nodeName = newName;
}

/**
 * get the name of the objNode.
 * @return name of the objNode
 */
std::string GameNode::getNodeName(){
    return nodeName;
}

/**
 * recursively find the objNode with the given ID
 * @param id ID to look for
 * @return the GameNode that contains that ID
 */
GameNode *GameNode::findNodeByName(std::string name) {
    if(nodeName == name){
        return this;
    }

    for(int i = 0; i < numbOfChildren; i++){
        if(children[i] != nullptr){
            GameNode * j = children[i]->findNodeByName(name);
            if(j != nullptr){return j;}
        }
    }
    return nullptr;
}

/**
 * free children from the memory
 */
void GameNode::freeChildren() {
    for(int i = 0; i < numbOfChildren; i++){
        freeChild(0);
    }
    numbOfChildren = 0;
}

/**
 * free a child at a given index
 * @param index the index that the child is at
 */
void GameNode::freeChild(int index) {
    if(index < numbOfChildren && index >= 0) {
        if(index == numbOfChildren - 1){    // child is the last one in the queue
            children[index]->freeChildren();
            delete children[index];
            children[index] = nullptr;
        }else{                              // child is not last in the queue
            children[index]->freeChildren();
            delete children[index];
            // put the last child in the deleted child spot
            children[index] = children[numbOfChildren - 1];
        }
    }
    numbOfChildren--;
}

void GameNode::print() {
    printf("NodeID: %s\n", nodeName.c_str());
    for(int i = 0; i < numbOfChildren; i++){
        if(children[i] != nullptr){
            children[i]->print();
        }
    }
}
