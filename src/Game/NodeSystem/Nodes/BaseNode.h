//
// Created by janha on 05/03/2024.
//

#ifndef MEP_BASENODE_H
#define MEP_BASENODE_H
#include <vector>
#include <algorithm>

class Node {
protected:
    unsigned int ID;
    std::vector<Node *> nextNode;

public:
    explicit Node(unsigned int id) : ID(id) {}

    void addNode(Node * newNodePtr){
        nextNode.push_back(newNodePtr);
    }

    void removeNode(unsigned int id){
        nextNode.erase(std::find(nextNode.begin(), nextNode.end(), getNode(id)));
    }

    [[nodiscard]] unsigned int getID() const{
        return ID;
    }

    Node * findNode(unsigned int nodeID){
        if(ID == nodeID){
            return this;
        }else{
            Node * nextNodePtr = getNode(nodeID);
            if(nextNodePtr != nullptr){
                return nextNodePtr;
            }
            for(Node* node : nextNode){
                nextNodePtr = node->findNode(nodeID);
                if(nextNodePtr != nullptr){
                    return nextNodePtr;
                }
            }
        }
        return nullptr;
    }

    Node * getNode(unsigned int id){
        for(Node* node : nextNode){
            if(node->getID() == id){
                return node;
            }
        }
        return nullptr;
    }
};

#endif //MEP_BASENODE_H
