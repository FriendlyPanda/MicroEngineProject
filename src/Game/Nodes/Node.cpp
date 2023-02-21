//
// Created by User on 16/02/2023.
//

#include "Node.h"

Node::Node() {
    content = nullptr;
    nodeName = "";
}

Node::Node(NodeEmpty * data) {
    content = std::move(data);
}



NodeEmpty *Node::getContent() {
    return (NodeEmpty *)content;
}

void Node::setContent(NodeEmpty *newContent) {
    content = newContent;
}

std::vector<Node *> Node::getAllNodes() {
    return nodes;
}

Node *Node::getNode(int index) {
    return nodes.at(index);
}

Node *Node::getParentNode() {
    return parentNode;
}

void Node::setParentNode(Node * newParent) {
    parentNode = newParent;
}

Node::~Node() {
    for(Node * node: nodes){
        delete node;
        node = nullptr;
    }
    nodes.clear();
    parentNode = nullptr;
    content = nullptr;
}

Node *Node::getNodeOfName(std::string nodeName) {
    if(this->nodeName == nodeName){
        return this;
    }
    Node * nodeLookedFor;
    for(Node * node: nodes){
        nodeLookedFor = node->getNodeOfName(nodeName);
        if(nodeLookedFor != nullptr){
            return nodeLookedFor;
        }
    }
    return nullptr;
}

void Node::addNode(Node *newNode) {
    nodes.push_back(newNode);
}

GameConfiguration *Node::getConfig() {
    if(gc == nullptr){
        if(parentNode != nullptr){
            return parentNode->getConfig();
        }
        return nullptr;
    }else{
        return gc;
    }
}

void Node::setNodeName(std::string newName) {
    nodeName = newName;
}

std::string Node::getName() {
    return nodeName;
}

void Node::setConfig(GameConfiguration * newGC) {
    gc = newGC;
}


