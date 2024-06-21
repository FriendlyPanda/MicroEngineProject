//
// Created by janha on 01/05/2024.
//

#ifndef MEP_NODE_OBJECT_H
#define MEP_NODE_OBJECT_H


#include "BaseNode.h"
#include "string"
#include "glm/vec3.hpp"

class Node_Object : public Node{
private:
    std::string name;
    glm::vec3 position;
    glm::vec3 rotation;
public:
    Node_Object(unsigned int id, std::string name);

    void setName(std::string newName);
    std::string getName() const;

    // position
    void setPosition(glm::vec3 newPos);
    void setPosition(float x, float y, float z);
    glm::vec3 getPosition() const;

    void X(float x);
    void addX(float x);
    float X() const;

    void Y(float y);
    void addY(float y);
    float Y() const;

    void Z(float z);
    void addZ(float z);
    float Z() const;

    // rotation
    void setRotation(glm::vec3 newRot);
    void setRotation(float x, float y, float z);
    glm::vec3 getRotation() const;

    void rotX(float x);
    float rotX() const;

    void rotY(float y);
    float rotY() const;

    void rotZ(float z);
    float rotZ() const;
};


#endif //MEP_NODE_OBJECT_H
