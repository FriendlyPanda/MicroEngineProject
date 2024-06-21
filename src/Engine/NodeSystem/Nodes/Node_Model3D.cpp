//
// Created by janha on 05/03/2024.
//

#include "Node_Model3D.h"

void Node_Model3D::setModel(Model *newModel) {
    this->model3D = newModel;
}

Node_Model3D::Node_Model3D(unsigned int id) : Node(id) {
    this->model3D = nullptr;
}

void Node_Model3D::draw(Shader * shader) {
    if(this->model3D != nullptr){
        model3D->Draw(*shader);
    }
}
