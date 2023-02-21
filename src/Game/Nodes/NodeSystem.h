//
// Created by User on 08/02/2023.
//

#ifndef MEP_NODESYSTEM_H
#define MEP_NODESYSTEM_H


#include "NodeEmpty.h"
#include "Node.h"
#include <typeinfo>
#include <fstream>

class NodeSystem {
private:
    Node * headNode;
public:
    NodeSystem();
    bool loadNodeTree(std::string path);
    bool saveNodeTree(std::string path);
    Node * getHeadNode();
    void remove(std::string nodeID);
    Node * get(std::string nodeID);
    bool add(std::string parentName, NodeEmpty * newChild, std::string newNodeName);
    bool set(std::string nodeID, Node * node);
    bool nodeExists(const std::string& nodeName);
    template <typename T>
    void getNodesOfType(std::vector<T> * nodeVec){
        printf("typeid(T).name %s\n", typeid(T).name());
        headNode->getNodesOfType<T>(nodeVec);
    };
    void print();
    ~NodeSystem();
};


#endif //MEP_NODESYSTEM_H
