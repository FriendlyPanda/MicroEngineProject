//
// Created by User on 24/01/2023.
//

#ifndef MEP_GAMENODE_H
#define MEP_GAMENODE_H

#include "GameConfiguration.h"
#include <ctime>
#include <vector>

/**
 * GameNodes, the game will be made up out of nodes, each objNode can have a single parent, and multiple children,
 * positionAndDimention can be global (relative to the window) or relative (to the parent)
 */
class GameNode {
protected:
    static const int maxChildren = 16;
    int numbOfChildren = 0;
    GameNode * parent;
    std::vector<GameNode *> children;
    std::string nodeName;
    bool relativePosition = false;
    bool relativeRotation = false;
    GameConfiguration * gc;
public:
    GameNode();
    void setParent(GameNode * newParent);
    GameNode * getParent();
    bool addChild(GameNode * newChild);
    void setChild(int index, GameNode * newChild);
    GameNode * getChild(int index);
    std::vector<GameNode *> getChildren();
    bool isRelativePosition();
    bool isRelativeRotation();
    void setRelativePosition(bool pos);
    void setRelativeRotation(bool rot);
    void setConfig(GameConfiguration * newgc);
    GameConfiguration * getConfig();
    ~GameNode();
    SDL_Rect sdlRect(int x, int y, int w, int h);
    SDL_Point sdlPoint(int x, int y);
    SDL_Rect sdlRectFromPoints(SDL_Point p1, SDL_Point p2);
    void freeChildren();
    void freeChild(int index);
    void print();
    void setNodeName(std::string newName);
    std::string getNodeName();
    GameNode *findNodeByName(std::string name);
    template<class T>
    T * getNodeOfType(){

    };
};




#endif //MEP_GAMENODE_H
