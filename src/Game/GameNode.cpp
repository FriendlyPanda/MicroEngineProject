//
// Created by janha on 01/02/2023.
//
#include "GameNode.h"

/**
 * basic constructor
 */
GameNode::GameNode() {
    SDL_Point newPosition = sdlPoint(0,0);
    position = &newPosition;
    gc = nullptr;
    parent = nullptr;
    children = new GameNode * [maxChildren];
    for(int i = 0; i < maxChildren; i++){
        children[i] = nullptr;
    }
    nodeID = -1;
}

/**
 * Set a new parent to the node.
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

    for(int i = 0; i < maxChildren; i++){
        if(children[i] == nullptr){
            children[i] = newChild;
            children[i]->setParent(this);
            return true;
        }
    }
    printf("WARNING: not enough space for children");
    return false;
}

/**
 * set a child at a indexed position.
 * @param index the index at which to put the child.
 * @param newChild the pointer to the new child.
 */
void GameNode::setChild(int index, GameNode *newChild) {
    delete (children[index]);
    children[index] = newChild;
}

/**
 * get a pointer to a child at specific index
 * @param index  the position of the child
 * @return the pointer to the child node
 */
GameNode *GameNode::getChild(int index) {
    return children[index];
}

/**
 * Get a list of children of the node
 * @return list of pointers to children nodes
 */
GameNode **GameNode::getChildren() {
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
 * Retrieves the config object pointer, if no pointer to an config object is set, the node asks the parent for the config object pointer, and sets it for itself.
 * The config object pointer can be set at any child node, and consequent child nodes will use the new config object pointer.
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
    //delete position;
    position = nullptr;

    gc = nullptr;
    freeChildren();
}

/**
 * get X position relative to the window, is not affected by relative positioning
 * @return X position relative to window
 */
int GameNode::getWindowRelativeX() {
    if(relativePosition){

    }else{

    }
    return 0;
}

/**
 * get Y position relative to the window, is not affected by relative positioning
 * @return Y position relative to window
 */
int GameNode::getWindowRelativeY() {
    return 0;
}

/**
 * This function returns X position relative to screen, does not matter if relative positioning is turned on or not.
 * @return X position relative to screen
 */
int GameNode::getScreenRelativeX() {
    return 0;
}

/**
 * This function returns Y position relative to screen, does not matter if relative positioning is turned on or not.
 * @return Y position relative to screen
 */
int GameNode::getScreenRelativeY() {
    return 0;
}

/**
 * A function to get x position of the node, if relative positioning is enabled the X will be relative to parent node origin
 * @return X position
 */
int GameNode::getX() {
    if(relativePosition){

    }
    return 0;
}

/**
 * Similar to getX, this function gets Y position
 * @return Y position
 */
int GameNode::getY() {
    return 0;
}

/**
 * Helper function to make rectangles easier
 * @param x x position
 * @param y y position
 * @param w width of the rectangle
 * @param h height of the rectangle
 * @return the complete rectangle
 */
SDL_Rect GameNode::sdlRect(int x, int y, int w, int h) {
    SDL_Rect rectangle = SDL_Rect();
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    return rectangle;
}

/**
 * Helper function to make points easier
 * @param x x position
 * @param y y position
 * @return SDL_Point the complete point
 */
SDL_Point GameNode::sdlPoint(int x, int y){
    SDL_Point point = SDL_Point();
    point.x = x;
    point.y = y;
    return point;
}

/**
 * Helper function to make rectangle from 2 points easier
 * @param p1 determines the x and y
 * @param p2 determines the w and h
 * @return SDL_Rect from 2 points
 */
SDL_Rect GameNode::sdlRectFromPoints(SDL_Point p1, SDL_Point p2) {
    return sdlRect(p1.x, p1.y, p2.x, p2.y);
}

/**
 * Returns the parent of the node, if node doesn't have a parent, return null
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
 * get the ID of the node
 * @return node ID
 */
unsigned int GameNode::getNodeID() {
    return nodeID;
}

/**
 * set the ID of the node
 * @param newID new ID
 */
void GameNode::setNodeID(unsigned int newID) {
    nodeID = newID;
}

/**
 * recursively find the node with the given ID
 * @param id ID to look for
 * @return the GameNode that contains that ID
 */
GameNode *GameNode::findNodeByID(unsigned int id) {
    if(nodeID == id){
        return this;
    }

    for(int i = 0; i < maxChildren; i++){
        if(children[i] != nullptr){
            GameNode * j = children[i]->findNodeByID(id);
            if(j != nullptr){return j;}
        }
    }
    return nullptr;
}

/**
 * free children from the memory
 */
void GameNode::freeChildren() {
    for(int i = 0; i < maxChildren; i++){
        freeChild(i);
    }
}

/**
 * free a child at a given index
 * @param index the index that the child is at
 */
void GameNode::freeChild(int index) {
    if(children[index] != nullptr) {
        delete children[index];
        children[index] = nullptr;
    }
}

void GameNode::print() {
    printf("NodeID: %d\n", nodeID);
    for(int i = 0; i < maxChildren; i++){
        if(children[i] != nullptr){
            children[i]->print();
        }
    }
}
