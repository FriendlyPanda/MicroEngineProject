//
// Created by janha on 01/05/2024.
//

#include "Node_Object.h"

#include <utility>

void Node_Object::setName(std::string newName) {
    this->name = std::move(newName);
}

Node_Object::Node_Object(unsigned int id, std::string name) : Node(id), name(std::move(name)) {
    this->position = glm::vec3(0.0);
    this->rotation = glm::vec3(0.0);
}


std::string Node_Object::getName() const {
    return this->name;
}

void Node_Object::setPosition(glm::vec3 newPos) {
    this->position = newPos;
}

void Node_Object::setPosition(float x, float y, float z) {
    this->position = glm::vec3(x,y,z);
}

glm::vec3 Node_Object::getPosition() const {
    return this->position;
}

void Node_Object::X(float x) {
    this->position.x = x;
}

float Node_Object::X() const {
    return this->position.x;
}

void Node_Object::Y(float y) {
    this->position.y = y;
}

float Node_Object::Y() const {
    return this->position.y;
}

void Node_Object::Z(float z) {
    this->position.z = z;
}

float Node_Object::Z() const {
    return this->position.z;
}

void Node_Object::setRotation(glm::vec3 newRot) {
    this->rotation = newRot;
}

void Node_Object::setRotation(float x, float y, float z) {
    this->rotation = glm::vec3(x,y,z);
}

glm::vec3 Node_Object::getRotation() const {
    return this->rotation;
}

void Node_Object::rotX(float x) {
    this->rotation.x = x;
}

float Node_Object::rotX() const {
    return this->rotation.x;
}

void Node_Object::rotY(float y) {
    this->rotation.y = y;
}

float Node_Object::rotY() const {
    return this->rotation.y;
}

void Node_Object::rotZ(float z) {
    this->rotation.z = z;
}

float Node_Object::rotZ() const {
    return this->rotation.z;
}

void Node_Object::addX(float x) {
    this->position.x += x;

}

void Node_Object::addY(float y) {
    this->position.y += y;
}

void Node_Object::addZ(float z) {
    this->position.z += z;
}
