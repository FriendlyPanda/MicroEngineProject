//
// Created by User on 08/02/2023.
//

#include "NodeSystem.h"

#include <utility>

/**
 * simple objNode constructor
 */
NodeSystem::NodeSystem() {
    headNode = new Node();
    headNode->setNodeName("GAME_HEAD_NODE");
}

/**
 * load Node tree from the file, specified in the path
 * @param path path to the objNode tree file
 * @return whether the read was successful
 */
bool NodeSystem::loadNodeTree(std::string path) {
    std::string nodeString;
    std::ifstream file(path);

    while(std::getline(file, nodeString)){

    }

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
 * get the head objNode of the objNode tree
 * @return head objNode
 */
Node * NodeSystem::getHeadNode() {
    return headNode;
}

/**
 * remove the objNode that has an ID of nodeID
 * @param nodeID the ID of the objNode to remove
 */
void NodeSystem::remove(std::string nodeName) {
    delete get(std::move(nodeName));
}

/**
 * get the objNode with the nodeID
 * @param nodeID the ID of the objNode
 * @return NodeEmpty pointer to a objNode
 */
Node * NodeSystem::get(std::string nodeName) {
    return headNode->getNodeOfName(std::move(nodeName));
}

/**
 * add a new child to the parent objNode.
 * @param parentName the parent to add the objNode to
 * @param newChild the new child objNode
 * @param newNodeName the name of the new node
 * @return whether the addition was successful
 */
bool NodeSystem::add(std::string parentName, NodeEmpty * newChild, std::string newNodeName) {
    Node * childNode = new Node();
    childNode->setNodeName(std::move(newNodeName));
    childNode->setContent(newChild);
    if(newChild != nullptr){
        newChild->setHost(childNode);
    }
    if(get(parentName) != nullptr){
        get(parentName)->addNode(childNode);
        return true;

    }else{
        printf("ERROR: parent is nullptr");
    }
    return false;
}

/**
 * set an existing objNode, existing children will be removed
 * @param nodeID ID of an existing objNode
 * @param node objNode that replaces the objNode
 * @return whether the replacement was successful
 */
bool NodeSystem::set(std::string nodeName, Node * node) {
    Node * nodeToReplace = get(std::move(nodeName));
    if(nodeToReplace != nullptr){
        delete nodeToReplace;
        nodeToReplace = node;
        return true;
    }
    return false;
}

/**
 * check whether the objNode with the nodeID existss in the tree.
 * @param nodeID ID of the objNode
 * @return whether the objNode exists or not
 */
bool NodeSystem::nodeExists(const std::string& nodeName) {
    headNode->getNodeOfName(nodeName);
    return (get(nodeName) != nullptr);
}



/**
 * simple objNode destructor
 */
NodeSystem::~NodeSystem() {
    delete headNode;
    headNode = nullptr;
}

void NodeSystem::print() {
    printf("Hello World\n");
}
