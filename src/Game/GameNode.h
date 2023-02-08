//
// Created by User on 24/01/2023.
//

#ifndef MEP_GAMENODE_H
#define MEP_GAMENODE_H

#include "GameConfiguration.h"
#include <ctime>

/**
 * GameNodes, the game will be made up out of nodes, each node can have a single parent, and multiple children,
 * position can be global (relative to the window) or relative (to the parent)
 */
class GameNode {
protected:
    static const int maxChildren = 16;
    int numbOfChildren = 0;
    GameNode * parent;
    GameNode ** children;
    unsigned int nodeID;
    bool relativePosition = false;
    bool relativeRotation = false;
    GameConfiguration * gc;
    SDL_Point * position;
    float angle = 0; // gonna use radians lol, 0 rad is right
public:
    GameNode();
    void setParent(GameNode * newParent);
    GameNode * getParent();
    bool addChild(GameNode * newChild);
    void setChild(int index, GameNode * newChild);
    GameNode * getChild(int index);
    GameNode ** getChildren();
    bool isRelativePosition();
    bool isRelativeRotation();
    void setRelativePosition(bool pos);
    void setRelativeRotation(bool rot);
    int getWindowRelativeX();
    int getWindowRelativeY();
    int getScreenRelativeX();
    int getScreenRelativeY();
    int getX();
    int getY();
    GameNode * findNodeByID(unsigned int id);
    void setConfig(GameConfiguration * newgc);
    GameConfiguration * getConfig();
    ~GameNode();
    SDL_Rect sdlRect(int x, int y, int w, int h);
    SDL_Point sdlPoint(int x, int y);
    SDL_Rect sdlRectFromPoints(SDL_Point p1, SDL_Point p2);
    unsigned int getNodeID();
    void setNodeID(unsigned int newID);
    void freeChildren();
    void freeChild(int index);
    void print();
};




#endif //MEP_GAMENODE_H
