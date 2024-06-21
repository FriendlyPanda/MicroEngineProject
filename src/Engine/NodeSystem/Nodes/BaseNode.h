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

//    void removeNode(unsigned int id){
//        nextNode.erase(std::find(nextNode.begin(), nextNode.end(), getNode(id)));
//    }

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

    Node * getParentNode(unsigned int id, Node * parent = nullptr){
        if(ID == id){
            return parent;
        }else{
            for(Node * node : nextNode){
                Node * locatedParent = node->getParentNode(id, this);
                if(locatedParent != nullptr){
                    return locatedParent;
                }
            }
        }
        return nullptr;
    }

    void removeNode(unsigned int id){
        Node * parent = getParentNode(id);
        if(parent == nullptr){
            return;
        }
        auto it = std::find_if(parent->nextNode.begin(), parent->nextNode.end(), [&](Node * n) {return n->getID() == id;});
        if(it != parent->nextNode.end()){
            Node * node = *it;
            parent->nextNode.erase(it);
            delete node;
        }
    }

    virtual ~Node() {
        for (auto node : nextNode){
            delete node;
        }
        nextNode.clear();
    }


};

#endif //MEP_BASENODE_H
