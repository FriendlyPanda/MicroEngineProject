//
// Created by janha on 01/02/2023.
//
#include "NodeEmpty.h"
#include "Node.h"

/**
 * basic constructor
 */
NodeEmpty::NodeEmpty() {
    host = nullptr;
}

/**
 * Retrieves the config object pointer, if no pointer to an config object is set, the objNode asks the parent for the config object pointer, and sets it for itself.
 * The config object pointer can be set at any child objNode, and consequent child nodes will use the new config object pointer.
 * @return GameConfiguration [pointer]
 */
GameConfiguration *NodeEmpty::getConfig() {
    return ((Node *) host)->getConfig();
}

/**
 * simple destructor
 */
NodeEmpty::~NodeEmpty() {
    host = nullptr;
}

/**
 * set the host of Node
 * @param hostNode
 */
void NodeEmpty::setHost(void *hostNode) {
    host = hostNode;
}

/**
 * get the pointer to the host
 * @return host
 */
void *NodeEmpty::getHost() {
    return host;
}
