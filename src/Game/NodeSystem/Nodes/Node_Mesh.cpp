//
// Created by janha on 01/05/2024.
//

#include "Node_Mesh.h"

Node_Mesh::Node_Mesh(unsigned int id) : Node(id) {}

void Node_Mesh::setMesh3D(Mesh * newMesh) {
    this->mesh3D = newMesh;
}

void Node_Mesh::draw(Shader *shader) {
    this->mesh3D->Draw(*shader);
}
