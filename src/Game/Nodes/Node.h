//
// Created by User on 16/02/2023.
//

#ifndef MEP_NODE_H
#define MEP_NODE_H

#include "NodeEmpty.h"
#include <vector>

class Node {
private:
    NodeEmpty *content;
    std::string nodeName;
    Node *parentNode;
    std::vector<Node *> nodes;
    GameConfiguration *gc;
public:
    Node();

    Node(NodeEmpty *data);

    NodeEmpty *getContent();

    void setContent(NodeEmpty *newContent);

    void addNode(Node *newNode);

    std::vector<Node *> getAllNodes();

    Node *getNode(int index);

    Node *getNodeOfName(std::string nodeName);

    Node *getParentNode();

    void setParentNode(Node *newParent);

    std::string getName();

    GameConfiguration *getConfig();

    void setConfig(GameConfiguration *);

    void setNodeName(std::string newName);


    /**
     * check if the content matches the required type to return
     * @tparam T the required type to return
     * @param returnList the
     */
    template<class T>
    void getNodesOfType(std::vector<T> *returnList) {
        if (content != nullptr && typeid(content) != typeid(NodeEmpty)) {
            printf("typeid(content).name %s\n", content->getType().name());
            if (content->getType() == typeid(T)) {
                printf("typeid(content).name FOUND %s\n", content->getType().name());
                returnList->push_back((T) content);
            }
        } else {
            printf("Missing content\n");
        }
        for (Node *node: nodes) {
            node->getNodesOfType(returnList);
        }
    };

    ~Node();
};


#endif //MEP_NODE_H
