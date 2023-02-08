//
// Created by User on 08/02/2023.
//

#ifndef MEP_NODESYSTEM_H
#define MEP_NODESYSTEM_H


#include "GameNode.h"
#include <typeinfo>

class NodeSystem {
private:
    GameNode * headNode;
    unsigned int size;
    unsigned int nextID;
public:
    NodeSystem();
    bool loadNodeTree(std::string path);
    bool saveNodeTree(std::string path);
    GameNode * getHeadNode();
    void remove(int nodeID);
    GameNode * get(int nodeID);
    bool add(int parentNodeID, GameNode * newChild);
    bool set(int nodeID, GameNode * node);
    bool nodeExists(int nodeID);
    template <typename T>
    T ** getNodesOfType();
    void print();
    ~NodeSystem();
};


#endif //MEP_NODESYSTEM_H
