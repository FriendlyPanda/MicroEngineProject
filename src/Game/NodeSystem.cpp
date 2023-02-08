//
// Created by User on 08/02/2023.
//

#include "NodeSystem.h"

/**
 * simple node constructor
 */
NodeSystem::NodeSystem() {
    headNode = new GameNode();
    headNode->setNodeID(0);
    size = 1;
    nextID = 1;
}

/**
 * load Node tree from the file, specified in the path
 * @param path path to the node tree file
 * @return whether the read was successful
 */
bool NodeSystem::loadNodeTree(std::string path) {
    return false;
}

/**
 * save the Node Tree to a file, specified by file
 * @param path the file to save, if file does not exists, new one will be created.
 * @return weather the write was successful
 */
bool NodeSystem::saveNodeTree(std::string path) {
    return false;
}

/**
 * get the head node of the node tree
 * @return head node
 */
GameNode * NodeSystem::getHeadNode() {
    return headNode;
}

/**
 * remove the node that has an ID of nodeID
 * @param nodeID the ID of the node to remove
 */
void NodeSystem::remove(int nodeID) {
    delete get(nodeID);
    size--;
}

/**
 * get the node with the nodeID
 * @param nodeID the ID of the node
 * @return GameNode pointer to a node
 */
GameNode * NodeSystem::get(int nodeID) {
    return headNode->findNodeByID(nodeID);
}

/**
 * add a new child to the parent node.
 * @param parentNodeID the parent to add the node to
 * @param newChild the new child node
 * @return whether the addition was successful
 */
bool NodeSystem::add(int parentNodeID, GameNode * newChild) {
    GameNode * parentNode = get(parentNodeID);
    if(parentNode != nullptr){
        newChild->setNodeID(size);
        parentNode->addChild(newChild);
        size++;
        nextID++;
    }
    return false;
}

/**
 * set an existing node, existing children will be removed
 * @param nodeID ID of an existing node
 * @param node node that replaces the node
 * @return whether the replacement was successful
 */
bool NodeSystem::set(int nodeID, GameNode * node) {
    GameNode * nodeToReplace = get(nodeID);
    if(nodeToReplace != nullptr){
        nodeToReplace->freeChildren();
        node->setNodeID(nodeToReplace->getNodeID());
        *nodeToReplace = *node;
        return true;
    }
    return false;
}

/**
 * check whether the node with the nodeID existss in the tree.
 * @param nodeID ID of the node
 * @return whether the node exists or not
 */
bool NodeSystem::nodeExists(int nodeID) {
    headNode->findNodeByID(nodeID);
    return (get(nodeID) != nullptr);
}



/**
 * simple node destructor
 */
NodeSystem::~NodeSystem() {
    delete headNode;
    headNode = nullptr;
    size = 0;
}

void NodeSystem::print() {
    headNode->print();
}

template<typename T>
T **NodeSystem::getNodesOfType() {

    int numbOfNodes = 0;
    T * nodes[0];
    for(int i = 0; i < size; i++){
        GameNode * nodeToCheck = get(i);
        if(nodeToCheck != nullptr){
            if(typeid(*nodeToCheck) == typeid(T)){
                numbOfNodes++;
                T * temp = nodes;
                nodes = new T*[numbOfNodes];
                for(int j = 0; j < numbOfNodes - 1; j++){
                    nodes[j] = temp[j];
                }
                delete[] temp;
            }
        }
    }
    return nodes;
}
